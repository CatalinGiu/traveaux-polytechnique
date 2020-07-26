package ca.polymtl.inf8480.tp1.server;

import ca.polymtl.inf8480.tp1.shared.ZipManager;

import java.io.*;
import java.util.*;

public class FileManager {

    private Map<String, String> files = new HashMap<>();
    private ZipManager zipManager = new ZipManager();

    public static final String path = "files/";

    public void zip(){
        zipManager.createZip(path, files);
    }

    public FileManager() {
        File folder = new File(path);
        if(!folder.exists()){
            folder.mkdir();
        }
        File[] listOfFiles = folder.listFiles();

        for(File file : listOfFiles){
            files.put(file.getName(), "non verouille");
        }
    }

    public boolean create(String filename){
        File file = new File(path + filename);
        if(file.exists()){
            return  false;
        }
        try{
            file.createNewFile();
            files.put(filename, "non verouille");
        }catch (IOException e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public Map list(){
        return files;
    }

    public String getlock(String filename, String uid){
        if(files.get(filename) != null ) {
            if (files.get(filename).equals("non verouille") || files.get(filename).equals(uid)) {
                files.put(filename, uid);
                return uid;
            } else {
                return files.get(filename);
            }
        }
        return null;
    }

    public boolean hasLock(String filename, String uid) {
        if (files.get(filename) != null && files.get(filename).equals(uid)) {
            return true;
        }
        return false;
    }

    public void releaseLock(String filename) {
        if (files.get(filename) != null) {
            files.put(filename, "non verouille");
        }
    }



}
