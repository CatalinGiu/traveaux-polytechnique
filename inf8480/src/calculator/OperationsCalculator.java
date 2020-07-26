package calculator;
import shared.Operation;

import java.util.ArrayList;
import java.util.Random;

public final class OperationsCalculator
{
    public static final String PELL = "pell";
    public static final String PRIME = "prime";
    public static final int MODULO_VALUE = 4000;

    public static ArrayList<Operation> calculateOperations(ArrayList<Operation> ops)
    {
        for (int i = 0; i < ops.size(); i++)
        {
            String operation = ops.get(i).operation;
            int operand = ops.get(i).operand;
            int opResult;
            if (isPellOperation(operation))
            {
                opResult = Operations.pell(operand);
            }
            else
            {
                opResult = Operations.prime(operand);
            }
            ops.get(i).result = opResult % MODULO_VALUE;
        }
        return ops;
    }


    public static ArrayList<Operation> calculateOperations(ArrayList<Operation> ops, boolean malicious, double rate )
    {
        for (int i = 0; i < ops.size(); i++)
        {
            String operation = ops.get(i).operation;
            int operand = ops.get(i).operand;
            int opResult;
            if(malicious && mustSendMaliciousData(rate)){
                System.out.println("I'm so funny");
                opResult = maliciousInt();
            }
            else if (isPellOperation(operation))
            {
                opResult = Operations.pell(operand);
            }
            else
            {
                opResult = Operations.prime(operand);
            }
            ops.get(i).result = opResult % MODULO_VALUE;
        }
        return ops;
    }

    private static int maliciousInt(){
        Random r = new Random();
        return r.nextInt(4000);
    }

    private static boolean mustSendMaliciousData(double maliciousRate)
    {
        Random r = new Random();
        double rDouble = r.nextDouble();
        return rDouble < maliciousRate;
    }

    public static boolean isPellOperation(String op)
    {
        return op.equals(PELL);
    }

    public static boolean isPrimeOperation(String op)
    {
        return op.equals(PRIME);
    }
}
