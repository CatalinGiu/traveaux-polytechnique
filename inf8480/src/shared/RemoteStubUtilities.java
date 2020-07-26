package shared;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public final class RemoteStubUtilities {

    public static ICatalog loadCatalogStub(String host){
        ICatalog stub = null;

        try {
            Registry registry = LocateRegistry.getRegistry(host);
            stub = (ICatalog) registry.lookup("catalog");
        } catch (NotBoundException e) {
            System.out.println("Erreur: Le nom '" + e.getMessage()
                    + "' n'est pas défini dans le registre.");
        } catch (RemoteException e) {
            System.out.println("Erreur: " + e.getMessage());
        }

        return stub;
    }

    public static ICalculator loadCalculatorStub(String host){
        ICalculator stub = null;

        try {
            Registry registry = LocateRegistry.getRegistry(host);
            stub = (ICalculator) registry.lookup("calculator");
        } catch (NotBoundException e) {
            System.out.println("Erreur: Le nom '" + e.getMessage()
                    + "' n'est pas défini dans le registre.");
        } catch (RemoteException e) {
            System.out.println("Erreur: " + e.getMessage());
        }

        return stub;
    }
}
