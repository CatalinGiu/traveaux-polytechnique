package ca.polymtl.inf8480.tp1.shared;

import java.io.FileOutputStream;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.util.Base64;

/**
 * fichier utilistaire pour ecrire un bitstream comme fichier, lire un fichier comme bitstream et trouver
 * la somme MD5
 */
public class FileUtilities {

    private byte[] fileBytes = null;
    public byte[] readFile(String name){

        try {
            fileBytes = Files.readAllBytes(Paths.get(name));
            return fileBytes;
        }catch (Exception e){
            //
        }
        return null;
    }

    public String getMd5(String filename){
        readFile(filename);
        try {
            byte[] md5 =  MessageDigest.getInstance("MD5").digest(fileBytes);
            return Base64.getEncoder().encodeToString(md5);
        }catch (Exception e){
            System.out.println("no such file");
        }
        return null;
    }

    public byte[] getFile(){
        return fileBytes;
    }


    public void write(byte[] content, String filename){
        FileOutputStream stream;
        try {
            stream = new FileOutputStream(filename);
            stream.write(content);
            stream.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


}
