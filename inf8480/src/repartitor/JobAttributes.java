package repartitor;

import shared.ICalculator;
import shared.Operation;

import java.util.ArrayList;
import java.util.Stack;

public class JobAttributes {
    private ICalculator calculatorStub;
    private Stack<Operation> ops = new Stack<>();
    private int taskSize;
    private ArrayList<Integer> result = new ArrayList<>();
    public ArrayList<Operation> workingOn;

    private ArrayList<Operation> executed = new ArrayList<>();
    public int blockID = -1;
    public String host;

    public JobAttributes(ICalculator calculatorStub, int taskSize) {
        this.calculatorStub = calculatorStub;
        this.taskSize = taskSize;
    }

    public ArrayList<Operation> getNextOpertations(){
        if(ops == null || ops.size() == 0){
            return null;
        }
        ArrayList<Operation> ret = new ArrayList<>();
        for(int i = 0; i < this.taskSize && !this.ops.empty(); i++){
            ret.add(this.ops.pop());
        }
        workingOn = ret;
        return ret;
    }


    public Stack<Operation> getOps() {
        return ops;
    }

    public void setOps(Stack<Operation> ops) {
        this.executed = new ArrayList<>();
        this.ops = ops;
    }

    public ArrayList<Integer> getResult() {
        return result;
    }

    public void addResult(int result) {
        this.result.add(result);
    }


    public ICalculator getCalculatorStub() {
        return calculatorStub;
    }

    public boolean jobDone(){
        return this.ops == null || this.ops.empty();
    }

    public int getTaskSize() {
        return taskSize;
    }

    public ArrayList<Operation> getExecuted() {
        return this.executed;
    }

    public void addExecuted(ArrayList<Operation> executedOps) {
        workingOn = null;
        executed.addAll(executedOps);
    }

    @Override
    public String toString() {
        return "JobAttributes{" +
                "ops=" + ops.size() +
                ", taskSize=" + taskSize +
                ", result=" + result +
                ", executed=" + executed.size() +
                ", blockID=" + blockID +
                ", host=" + host +
                '}';
    }
}
