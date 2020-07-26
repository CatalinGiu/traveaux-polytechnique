package shared;

import java.io.Serializable;

public class Operation implements Serializable
{
    public String operation;
    public int operand;
    public int result;

    public Operation()
    {

    }

    public Operation(String operation, int operand)
    {
        this.operation = operation;
        this.operand = operand;
    }

    @Override
    public String toString() {
        return "Operation{" +
                "operation='" + operation + '\'' +
                ", operand=" + operand +
                ", result=" + result +
                '}';
    }
}
