package catalog;

import shared.CatalogEntry;
import shared.ICatalog;

import java.rmi.ConnectException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class Catalog implements ICatalog {
    private Set<CatalogEntry> hosts = new HashSet<>();
    private HashMap<String,String> repartitors = new HashMap<>();

    @Override
    public void registerHost(String host, int ressources) throws RemoteException {
        this.hosts.add(new CatalogEntry(host, ressources));
        // On affiche le contenu pour faciliter le debuggage
        System.out.println(hosts);
    }

    @Override
    public boolean authoriseRepartitor(String username, String password) throws RemoteException {
        if(repartitors.get(username) != null){
            if (repartitors.get(username).equals(password)){
                return true;
            }
            else {
                return false;
            }
        }
        repartitors.put(username, password);
        return true;
    }

    @Override
    public Set<CatalogEntry> getHosts(String username, String password) throws RemoteException {
        System.out.println("Request for registered hosts: "+ username + "\t");
        if(authoriseRepartitor(username, password)){
            return this.hosts;
        }
        return null;

    }

    @Override
    public String hello(String name) throws RemoteException {
        String concat = "Catalog : Hello " + name;
        System.out.println(concat);
        return concat;
    }

    public static void main(String[] args){
        Catalog catalog = new Catalog();
        catalog.run();
    }

    private void run() {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            ICatalog stub = (ICatalog) UnicastRemoteObject
                    .exportObject(this, 0);

            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("catalog", stub);
            System.out.println("Catalog ready.");
        } catch (ConnectException e) {
            System.err
                    .println("Impossible de se connecter au registre RMI. Est-ce que rmiregistry est lancé ?");
            System.err.println();
            System.err.println("Erreur: " + e.getMessage());
        } catch (Exception e) {
            System.err.println("Erreur: " + e.getMessage());
        }
    }

}
