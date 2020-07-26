package ca.polymtl.inf8480.tp1.shared;

import ca.polymtl.inf8480.tp1.client.Client;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

class ZipManagerTest {

    @Test
    void createZip(){
        Map<String, String> files = new HashMap<>();
        String path = "files/";
        File folder = new File(path);
        File[] listOfFiles = folder.listFiles();

        for(File file : listOfFiles){
            files.put(file.getName(), "non verouille");
        }
        ZipManager zm = new ZipManager();
        assert(zm.createZip(path, files) != null);
    }


    @Test
    void unzip(){
        ZipManager zm = new ZipManager();
        assert(zm.unzip());
    }

}