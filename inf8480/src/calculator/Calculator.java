package calculator;

import shared.RemoteStubUtilities;
import shared.ICalculator;
import shared.ICatalog;

import java.rmi.ConnectException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import java.util.ArrayList;

import java.util.Random;

import shared.Operation;

public class Calculator implements ICalculator {

    private ICatalog catalogStub = null;
    private int maxCapacity = 0;
    private boolean isMalicious = false;
    private double maliciousRate = 0.05;

    public Calculator() {
        super();
    }

    public static void main(String[] args){
        if (args.length < 4)
        {
            System.out.println("Bad argument count for repartitor main");
            System.exit(0);
        }
        Calculator calculator = new Calculator();
        calculator.run(args);
    }

    private void run(String[] args) {
        catalogStub = RemoteStubUtilities.loadCatalogStub(args[0]);
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            ICalculator stub = (ICalculator) UnicastRemoteObject
                    .exportObject(this, 0);

            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("calculator", stub);
            System.out.println("Calculator ready.");
            setMaxCapacity(Integer.parseInt(args[2]));
            catalogStub.registerHost(args[1], this.maxCapacity);
            this.isMalicious = Boolean.valueOf(args[3]);
            if(this.isMalicious){
                if(args.length == 5){
                    this.maliciousRate = Double.valueOf(args[4]);
                }
            }
        } catch (ConnectException e) {
            System.err
                    .println("Impossible de se connecter au registre RMI. Est-ce que rmiregistry est lancé ?");
            System.err.println();
            System.err.println("Erreur: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Erreur: " + e.getMessage());
        }
    }

    @Override
    public int calculate(ArrayList<Operation> ops)
    {
        System.out.println("received operations : " + ops.size());
//        if (mustSendMaliciousData())
//        {
//            Random r = new Random();
//            int rInt = r.nextInt();
//            return rInt;
//        }
//        else
            if (accept(ops.size()))
        {
            int ret = 0;
            for(Operation op : OperationsCalculator.calculateOperations(ops)){
                ret = (ret + op.result) % 4000;
            }
            return ret;
        }
        else
        {
            return -3;
        }
    }

    @Override
    public ArrayList<Operation> calculateNotSecure(ArrayList<Operation> ops) throws RemoteException {
        System.out.println("received operations : " + ops.size());
        if (accept(ops.size()))
        {
            return OperationsCalculator.calculateOperations(ops, this.isMalicious, this.maliciousRate);
        }
        else
        {
            return null;
        }
    }

    @Override
    public String hello(String name) throws RemoteException {
        return "Calculator : Hello " + name;
    }


    public boolean accept(int opsCount)
    {
        if (opsCount <= maxCapacity || isNotSurcharged(opsCount))
        {
            return true;
        }
        return false;

    }

    public boolean isNotSurcharged(int opsCount)
    {
        Random r = new Random();
        double rDouble = r.nextDouble();
        return rDouble >= calculateRefusalRate(opsCount);
    }

    public double calculateRefusalRate(int opsCount)
    {
        return ((double)(opsCount - maxCapacity)) / (5 * maxCapacity);
    }

    public int getMaxCapacity()
    {
        return maxCapacity;
    }

    public void setMaxCapacity(int newCapacity)
    {
        this.maxCapacity = newCapacity;
    }

    public boolean isMalicious()
    {
        return isMalicious;
    }

    public void setMalicious(boolean isMalicious)
    {
        this.isMalicious = isMalicious;
    }



}
