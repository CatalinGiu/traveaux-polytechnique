package ca.polymtl.inf8480.tp1.shared;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Map;
import java.util.UUID;

/**
 * interface du serveur
 */
public interface ServerInterface extends Remote {
	UUID createClientID() throws RemoteException;
	boolean create(String filename) throws RemoteException;
	Map list() throws RemoteException;
	byte[] sync() throws RemoteException;
	byte[] get(String nom, String checksum) throws RemoteException;
	String lock(String name, String clientId, String checksum) throws RemoteException;
	boolean push(String nom, byte[] content, String client) throws RemoteException;

}
