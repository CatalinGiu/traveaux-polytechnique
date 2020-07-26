package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Set;

public interface ICatalog extends Remote{
    void registerHost(String host, int ressources) throws RemoteException;
    boolean authoriseRepartitor(String username, String password) throws RemoteException;
    Set<CatalogEntry> getHosts(String username, String password) throws RemoteException;

    // Fonction pour tester la communication bidirectionelle
    String hello(String name) throws RemoteException;
}
