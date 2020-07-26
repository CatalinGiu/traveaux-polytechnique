package ca.polymtl.inf8480.tp1.client;

import java.io.*;
import java.rmi.AccessException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.UUID;

import ca.polymtl.inf8480.tp1.server.FileManager;
import ca.polymtl.inf8480.tp1.shared.FileUtilities;
import ca.polymtl.inf8480.tp1.shared.ServerInterface;
import ca.polymtl.inf8480.tp1.shared.ZipManager;

public class Client {
	private UUID id;
	private static String ip = "132.207.12.108";
	private FileUtilities fileUtilities = new FileUtilities();
	private ZipManager zipManager = new ZipManager();


	public static void main(String[] args) {

		Client.getIp(args);
		Client client = new Client(ip);
		client.run(args);
	}
	private ServerInterface distantServerStub = null;

	public Client(String distantServerHostname) {
		super();

		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}
		distantServerStub = loadServerStub(distantServerHostname);

	}

	private void run(String[] args) {

		appelRMI(args);

	}

	private ServerInterface loadServerStub(String hostname) {
		ServerInterface stub = null;

		try {
			Registry registry = LocateRegistry.getRegistry(hostname);
			stub = (ServerInterface) registry.lookup("server");
		} catch (NotBoundException e) {
			System.out.println("Erreur: Le nom '" + e.getMessage()
					+ "' n'est pas défini dans le registre.");
		} catch (AccessException e) {
			System.out.println("Erreur: " + e.getMessage());
		} catch (RemoteException e) {
			System.out.println("Erreur: " + e.getMessage());
		}

		return stub;
	}


	private void appelRMI(String[] args) {
		getId();
		try {
			switch (args[0]){
				case "list":
					System.out.println(distantServerStub.list());
					break;
				case "create" :
					if(distantServerStub.create(args[1])){
						System.out.println(args[1] + " ajoute.");
					}
					else {
						System.out.println("erreur.");
					}
					break;
				case "get" :
					byte[] file = distantServerStub.get(args[1], fileUtilities.getMd5(FileManager.path + args[1]));
					if( file != null) {
						fileUtilities.write(file, FileManager.path + args[1]);
						System.out.println(args[1] + " synchronise.");
					}
					else {
						System.out.println("erreur");
					}
					break;
				case "syncLocalDirectory" :
					File f = new File("files");
					if(f.exists()) {
						String[] entries = f.list();
						for (String s : entries) {
							File currFile = new File(f.getPath(), s);
							currFile.delete();
						}
					}
					fileUtilities.write(distantServerStub.sync(), "sync.zip");
					zipManager.unzip();
					System.out.println("dossier sunchronise");
					break;
				case "push" :
					if(distantServerStub.push(args[1], fileUtilities.readFile(FileManager.path + args[1]), id.toString())){
						System.out.println(args[1] + " envoye au serveur");
					}
					else {
						System.out.println("erreur");
					}
					break;
				case "lock" :
					String md5 = fileUtilities.getMd5(FileManager.path + args[1]);
					String lock = distantServerStub.lock(args[1], id.toString(), md5);
					if(lock.equals(id.toString())){
						System.out.println(args[1] + " verouille");
					}
					else if (lock != null){
						System.out.println(args[1] + " est deja verouille par " + lock);
					}
					break;
				default:
					System.out.println("entree invalide");
					System.out.println("si voulez modifiez l'adresse ip. changez la premiere ligne de 'ip.txt'");



			}


		} catch (RemoteException e) {
			System.out.println("Erreur: " + e.getMessage());
			e.printStackTrace();
		}
	}

	private void getId(){
		try {
			File file = new File("id.txt");
			if(file.exists()) {
				FileReader fr = new FileReader(file);
				BufferedReader br = new BufferedReader(fr);
				id = UUID.fromString(br.readLine());
			}
			else {
				file.createNewFile();
				FileWriter fw = new FileWriter(file);
				BufferedWriter bw = new BufferedWriter(fw);
				id = distantServerStub.createClientID();
				bw.write(id.toString());
				bw.close();
				fw.close();

			}
		}catch (Exception e){
			System.out.println("file id.txt error");
			e.printStackTrace();
		}
		System.out.println("votre id est : " + id);
	}

	private static void getIp(String[] args){
		try {
			File file = new File("ip.txt");
			if(file.exists()) {
				FileReader fr = new FileReader(file);
				BufferedReader br = new BufferedReader(fr);
				ip = br.readLine();
			}
			else {
				file.createNewFile();
				FileWriter fw = new FileWriter(file);
				BufferedWriter bw = new BufferedWriter(fw);
				ip = args[0];
				System.out.println(args[0]);
				bw.write(ip);
				bw.flush();
				bw.close();
				fw.close();

			}
		}catch (Exception e){
			System.out.println("file ip.txt error");
			e.printStackTrace();
		}
	}
}
