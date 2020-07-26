package ca.polymtl.inf8480.tp1.server;

import ca.polymtl.inf8480.tp1.shared.FileUtilities;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FileManagerTest {
    @Test
    void list() {
        FileManager fm = new FileManager();
        System.out.println(fm.list());
        assert(fm.list() != null);
    }

    @Test
    void MD5() {
        FileManager fm = new FileManager();
        FileUtilities fileUtilities = new FileUtilities();
        System.out.println(fileUtilities.getMd5("server"));
        fileUtilities.write(fileUtilities.getFile(), "1.txt");
    }

}