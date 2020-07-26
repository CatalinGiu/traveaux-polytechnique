package repartitor;
import java.io.*;
import java.util.Stack;

import shared.Operation;

public final class OperationsFileParser {

    public static Stack<Operation> parseOperationsFile(File file)
    {
        int lineCount = 0; //For debugging purposes
        Stack<Operation> operations = new Stack<>();
        try
        {
            FileReader reader = new FileReader(file);
            BufferedReader in = new BufferedReader(reader);
            String lineStr;
            while ((lineStr = in.readLine()) != null) {
                String[] splittedOperation = lineStr.split("\\s+");
                if (splittedOperation.length != 2) {
                    throw new Exception();
                }
                Operation newOperation = new Operation();
                newOperation.operation = splittedOperation[0];
                newOperation.operand = Integer.parseInt(splittedOperation[1]);
                operations.push(newOperation);
                lineCount++;
            }
        }
        catch (IOException e)
        {
            System.out.println("Error when trying to parse the file with path: " + file.getAbsolutePath());
            System.exit(0);
        }
        catch (Exception e)
        {
            System.out.println("Error parsing at line: " + lineCount + ". Verify that the file format is correct");
            System.exit(0);
        }
        return operations;
    }

}
