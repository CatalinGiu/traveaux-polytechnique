import org.junit.jupiter.api.Test;
import repartitor.CalculatorsManager;

import static org.junit.jupiter.api.Assertions.*;

class CalculatorsManagerTest {
    @Test
    void test() {
        CalculatorsManager man = new CalculatorsManager("localhost");
//        System.out.println(man.numberOfTasksToSend(5));
    }

}