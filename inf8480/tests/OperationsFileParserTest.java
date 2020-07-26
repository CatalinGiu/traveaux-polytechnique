import org.junit.jupiter.api.Test;

import java.io.File;
import java.util.Stack;

import repartitor.OperationsFileParser;
import shared.Operation;

import static org.junit.jupiter.api.Assertions.*;

class OperationsFileParserTest {

    @Test
    void parseOperationsFile() {
        String filePath = "ops/TestParseOne";
        File file = new File(filePath);
        if (!file.exists())
        {
            System.out.println("File does not exist");
            System.exit(0);
        }
        file.setReadOnly();
        Stack<Operation> stack = OperationsFileParser.parseOperationsFile(file);
        assertEquals(6, stack.size());

        assertEquals("prime", stack.get(0).operation);
        assertEquals(5571, stack.get(0).operand);

        assertEquals("prime", stack.get(1).operation);
        assertEquals(6575, stack.get(1).operand);

        assertEquals("prime", stack.get(2).operation);
        assertEquals(8868, stack.get(2).operand);

        assertEquals("prime", stack.get(3).operation);
        assertEquals(9251, stack.get(3).operand);

        assertEquals("pell", stack.get(4).operation);
        assertEquals(24, stack.get(4).operand);

        assertEquals("prime", stack.get(5).operation);
        assertEquals(7579, stack.get(5).operand);


    }
}