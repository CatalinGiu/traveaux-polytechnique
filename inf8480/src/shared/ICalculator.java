package shared;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import shared.Operation;

public interface ICalculator extends Remote
{
    int calculate(ArrayList<Operation> ops) throws RemoteException;
    ArrayList<Operation> calculateNotSecure(ArrayList<Operation> ops) throws RemoteException;

    //pour les tests
    String hello(String name) throws RemoteException;
}
