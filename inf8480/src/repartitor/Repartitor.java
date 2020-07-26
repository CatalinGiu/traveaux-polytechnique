package repartitor;


import java.io.*;
import java.util.*;
import java.util.concurrent.*;

import shared.ICalculator;
import shared.Operation;

public class Repartitor {

    private ArrayList<JobAttributes> jobAttributes = new ArrayList<>();
    private Stack<Operation> ops;
    private boolean secure = true;
    private int result = 0;
    private String username;
    private String password;
    private boolean errorOccured;


    public static void main(String[] args){

        if (args.length != 5)
        {
            System.out.println("Bad argument count for repartitor main");
            System.exit(0);
        }
        Repartitor repartitor = new Repartitor(args);

        repartitor.run();
    }

    public Repartitor(String[] args) {
        username = args[3];
        password = args[4];
        CalculatorsManager cm;
        try {
            cm = new CalculatorsManager(args[0], username, password);
            this.jobAttributes = cm.getJobAttributes();
        }catch (Exception e){
            System.out.println(e.getMessage());
            System.exit(1);
        }

        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        getOperations(args[1]);
        this.secure = Boolean.valueOf(args[2]);
    }

    private void run(){
        if(secure) {
            runSecure();
        }
        else{
            runNotSecure();
        }
    }

    private void runSecure(){
        splitSecureOps();
        startThreads();

        for(JobAttributes ja : this.jobAttributes){
            for(Operation op : ja.getExecuted()){
                System.out.println(result + " + " + op.result);
                this.result = (this.result + op.result) % 4000;
            }
        }
        if(this.ops.isEmpty()){
            System.out.println("Result : " + this.result);
        }
        else {
            runSecure();
        }
    }


    private void runNotSecure(){
        splitNotSecureOps();
        startThreads();
        if(!this.errorOccured) {

            for (int i = 0; i < jobAttributes.size() / 2; i++) {
                ArrayList<Operation> ops1 = jobAttributes.get(i).getExecuted();
                ArrayList<Operation> ops2 = jobAttributes.get(jobAttributes.size() - i - 1).getExecuted();

                for (int j = 0; j < ops1.size(); j++) {
                    if (ops1.get(j).result == ops2.get(j).result) {
                        result = (result + ops1.get(j).result) % 4000;
                    } else {
                        this.ops.push(ops1.get(j));
                    }
                }
            }
            int jobsize = jobAttributes.size() / 2;
            for (int i = 0; i < jobsize; i++) {
                this.jobAttributes.remove(jobsize - i - 1);
            }
            if (this.ops.empty()) {
                System.out.println("Result : " + this.result);
            } else {
                runNotSecure();
            }
        }
        else {
            this.errorOccured = false;
            for(JobAttributes ja : this.jobAttributes){
                for(Operation op : ja.getExecuted()){
                    this.ops.push(op);
                }
            }
            runNotSecure();
        }
    }

    private void getOperations(String path){
        File file = new File(path);
        if (!file.exists())
        {
            System.out.println("File does not exist");
            System.exit(0);
        }
        file.setReadOnly();
        this.ops = OperationsFileParser.parseOperationsFile(file);

    }

    private void splitSecureOps(){

        if(this.jobAttributes.size() == 0){
            System.out.println("No available calculator servers");
            System.exit(1);
        }

        int opsPerServer = (this.ops.size() / this.jobAttributes.size()) + 1;
        for(int i = 0; i < this.jobAttributes.size(); i++){
            Stack<Operation> stack = new Stack<>();
            for(int j = 0; j < opsPerServer && !this.ops.empty(); j++){
                stack.push(this.ops.pop());
            }
            this.jobAttributes.get(i).setOps(stack);
            this.jobAttributes.get(i).blockID = i;
        }
    }

    private void splitNotSecureOps(){

        if(this.jobAttributes.size() == 0){
            System.out.println("No available calculator servers");
            System.exit(1);
        }

        int numberOfJobs = this.jobAttributes.size();
        for(int i = 0; i < numberOfJobs; i++){
            JobAttributes tmpja = new JobAttributes(this.jobAttributes.get(i).getCalculatorStub(), this.jobAttributes.get(i).getTaskSize());
            tmpja.host = this.jobAttributes.get(i).host;
            this.jobAttributes.add(tmpja);
        }

        int opsToExecute = this.ops.size() * 2;
        int blockSize = (opsToExecute / this.jobAttributes.size()) + 1;

        for(int i = 0; i < this.jobAttributes.size() / 2; i++){
            Stack<Operation> stack = new Stack<>();
            Stack<Operation> stackCopy = new Stack<>();

            for (int j = 0; j < blockSize && !this.ops.empty(); j++){
                Operation elem = this.ops.pop();
                stack.push(elem);
                stackCopy.push(new Operation(elem.operation, elem.operand));
            }

            this.jobAttributes.get(i).setOps(stack);
            this.jobAttributes.get(i).blockID = i;

            int indexVerif = this.jobAttributes.size() - i - 1;

            this.jobAttributes.get(indexVerif).setOps(stackCopy);
            this.jobAttributes.get(indexVerif).blockID = i;

        }
    }

    private void startThreads(){
        ExecutorService pool;
        if(this.secure) {
            pool = Executors.newFixedThreadPool(this.jobAttributes.size());
        }
        else {
            pool = Executors.newFixedThreadPool(this.jobAttributes.size() / 2);
        }
        Set<Future<JobAttributes>> set = new HashSet<>();

        for (JobAttributes ja : this.jobAttributes) {
            Callable<JobAttributes> callable = new Job(ja);
            Future<JobAttributes> future = pool.submit(callable);
            set.add(future);
        }


        for (Future<JobAttributes> future : set) {
            try {
                future.get();
            }catch (Exception e){
                System.out.println("Erreur dans les threads");
            }
        }

        removeBadServers();
        pool.shutdown();

    }

    private class Job implements Callable<JobAttributes> {
        Job(JobAttributes jobAttributes) {
            this.jobAttributes = jobAttributes;
        }

        private JobAttributes jobAttributes;

        @Override
        public JobAttributes call() throws Exception {
            ICalculator calculator = this.jobAttributes.getCalculatorStub();
            ArrayList<Operation> ret;
            ArrayList<Operation> ops;
            while (!this.jobAttributes.jobDone()){
                ops = this.jobAttributes.getNextOpertations();
                do{
                    ret = calculator.calculateNotSecure(ops);
                }while (ret == null);
                this.jobAttributes.addExecuted(ret);

            }
            return this.jobAttributes;
        }
    }

    private void removeBadServers(){
        String badhost = null;

        for(int i = 0; i < this.jobAttributes.size(); i++){
            if(!this.jobAttributes.get(i).jobDone()){
                badhost = this.jobAttributes.get(i).host;
                this.errorOccured = true;
            }
        }

        if(badhost != null) {
            System.out.println("job size before cleaning :" + this.jobAttributes.size());
            int numberOfJobs = this.jobAttributes.size() - 1;
            System.out.println("CLEANING");
            for (int i = numberOfJobs; i >= 0; i--) {
                System.out.println("CHECKING: " + this.jobAttributes.get(i));
                if (this.jobAttributes.get(i).host.equals(badhost)) {
                    System.out.println("REMOVING: " + this.jobAttributes.get(i));
                    this.jobAttributes.remove(i);
                }
            }
            System.out.println("job size after cleaning :" + this.jobAttributes.size());
        }
    }

}
