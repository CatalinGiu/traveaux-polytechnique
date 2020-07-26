package ca.polymtl.inf8480.tp1.server;

import java.rmi.ConnectException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

import ca.polymtl.inf8480.tp1.shared.FileUtilities;
import ca.polymtl.inf8480.tp1.shared.ServerInterface;

public class Server implements ServerInterface {

	private UuidFileManager uuidFM = UuidFileManager.getInstance();
	private FileManager fileManager = new FileManager();
	private FileUtilities fileUtilities = new FileUtilities();

	public static void main(String[] args) {
		Server server = new Server();
		server.run();
	}

	public Server() {
		super();
	}

	private void run() {
		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}

		try {
			ServerInterface stub = (ServerInterface) UnicastRemoteObject
					.exportObject(this, 0);

			Registry registry = LocateRegistry.getRegistry();
			registry.rebind("server", stub);
			System.out.println("Server ready.");
		} catch (ConnectException e) {
			System.err
					.println("Impossible de se connecter au registre RMI. Est-ce que rmiregistry est lancé ?");
			System.err.println();
			System.err.println("Erreur: " + e.getMessage());
		} catch (Exception e) {
			System.err.println("Erreur: " + e.getMessage());
		}
	}


	/**
	 * methode pour genrer un identifiant unique pour le client
	 * @return UUID
	 */
	@Override
	public UUID createClientID(){
		UUID id = UUID.randomUUID();
		uuidFM.writeId(id);
		return id;
	}

	@Override
	public boolean create(String filename){
		return fileManager.create(filename);
	}


	@Override
	public Map list(){
		return fileManager.list();
	}

	@Override
	public byte[] sync(){
		fileManager.zip();
		return fileUtilities.readFile("sync.zip");
	}

	@Override
	public byte[] get(String name, String checksum){
		if(fileUtilities.getMd5(FileManager.path + name).equals(checksum)){
			return null;
		}
		return fileUtilities.getFile();
	}

	@Override
	public String lock(String name, String clientId, String checksum){
		return fileManager.getlock(name, clientId);
	}

	@Override
	public boolean push(String nom, byte[] content, String client){
		if(fileManager.hasLock(nom, client)){
			fileUtilities.write(content, FileManager.path + nom);
			fileManager.releaseLock(nom);
			return true;
		}
		return false;
	}

}
