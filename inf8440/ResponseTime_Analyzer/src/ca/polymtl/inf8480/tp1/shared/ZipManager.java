package ca.polymtl.inf8480.tp1.shared;

import java.io.*;
import java.util.Enumeration;
import java.util.Map;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipOutputStream;

/**
 * tire de http://www.avajava.com/tutorials/lessons/how-can-i-create-a-zip-file-from-a-set-of-files.html
 * http://www.avajava.com/tutorials/lessons/how-do-i-unzip-the-contents-of-a-zip-file.html;jsessionid=50BFA10CCBDFA216CF80A76EF732381A
 *
 * ceci est un utilistaire pour ziper les contenu d'un folder
 */
public class ZipManager {

    private final  String ZIPNAME = "sync.zip";
    public String createZip(String path, Map<String, String> files){
        String ret = null;
        FileOutputStream fos = null;
        ZipOutputStream zos = null;
        try {
            fos= new FileOutputStream(ZIPNAME);
            zos = new ZipOutputStream(fos);

            for(String filename : files.keySet()){
                addToZipFile(path + filename, zos);
            }
            ret = ZIPNAME;
        }catch (Exception e) {
            e.printStackTrace();
        }finally {
            closeQuietly(zos);
            closeQuietly(fos);
        }

        return  ret;
    }


    private static void addToZipFile(String fileName, ZipOutputStream zos) throws FileNotFoundException, IOException {

        System.out.println("Writing '" + fileName + "' to zip file");

        File file = new File(fileName);
        FileInputStream fis = new FileInputStream(file);
        ZipEntry zipEntry = new ZipEntry(fileName);
        zos.putNextEntry(zipEntry);

        byte[] bytes = new byte[1024];
        int length;
        while ((length = fis.read(bytes)) >= 0) {
            zos.write(bytes, 0, length);
        }

        zos.closeEntry();
        fis.close();
    }

    public void closeQuietly(Closeable closeable) {
        if (closeable != null) {
            try {
                closeable.close();
            } catch (IOException ex) {
                // ignore
            }
        }
    }

    public boolean unzip(){
        try {
            ZipFile zipFile = new ZipFile(ZIPNAME);
            Enumeration<?> enu = zipFile.entries();
            while (enu.hasMoreElements()) {
                ZipEntry zipEntry = (ZipEntry) enu.nextElement();

                String name = zipEntry.getName();

                File file = new File(name);
                if (name.endsWith("/")) {
                    file.mkdirs();
                    continue;
                }

                File parent = file.getParentFile();
                if (parent != null) {
                    parent.mkdirs();
                }

                InputStream is = zipFile.getInputStream(zipEntry);
                FileOutputStream fos = new FileOutputStream(file);
                byte[] bytes = new byte[1024];
                int length;
                while ((length = is.read(bytes)) >= 0) {
                    fos.write(bytes, 0, length);
                }
                is.close();
                fos.close();

            }
            zipFile.close();
            return true;
        } catch (IOException e) {
            System.out.println("error unzipping file received from server");
            e.printStackTrace();
        }

        return false;
    }
}
