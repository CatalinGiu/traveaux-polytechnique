package ca.polymtl.inf8480.tp1.server;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class UuidFileManager {

    private static UuidFileManager instance;

    public static UuidFileManager getInstance(){
        if(instance == null){
            instance = new UuidFileManager();
        }
        return instance;
    }


    private File file;
    private List<UUID> Uuids = new ArrayList<>();
    private BufferedWriter bw;

    private UuidFileManager(){
        file = new File("UUIDs.txt");
        try{
            file.createNewFile();
        }catch (Exception e){
            System.out.println("Error creating file UUIDs.txt");
        }


        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String uuid;

            while((uuid = br.readLine()) != null){
                Uuids.add(UUID.fromString(uuid));
            }
            br.close();
            fr.close();

            FileWriter fw = new FileWriter(file);
            bw = new BufferedWriter(fw);

        }catch (Exception e){
            System.out.println("file UUIDs.txt error");
            e.printStackTrace();
        }
    }

    public void writeId(UUID id){
        try{
            bw.write(id.toString());
            bw.newLine();
            bw.flush();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

}
