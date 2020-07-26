package repartitor;

import shared.CatalogEntry;
import shared.ICatalog;

import java.util.ArrayList;
import java.util.Set;

import shared.RemoteStubUtilities;

public class CalculatorsManager {

    private ArrayList<JobAttributes> jobAttributes = new ArrayList<>();
    private ICatalog catalogStub = null;

    public CalculatorsManager(String calculatorList, String username, String password) throws Exception{
        this.catalogStub = RemoteStubUtilities.loadCatalogStub(calculatorList);
        Set<CatalogEntry> hosts;
        hosts = this.catalogStub.getHosts(username, password);
        if (hosts == null){
            throw new Exception("You don't have the permission with those credentials");
        }
        for (CatalogEntry entry : hosts){
            JobAttributes ja = new JobAttributes(
                    RemoteStubUtilities.loadCalculatorStub(entry.getHostname()),
                    numberOfTasksToSend(entry.getRessources()));
            ja.host = entry.getHostname();
            this.jobAttributes.add(ja);
        }

    }


    public ArrayList<JobAttributes> getJobAttributes(){
        return this.jobAttributes;
    }

    private int numberOfTasksToSend(int ressources){
        double ACCEPTABLE_REFUSAL_RATE = 0.3;
        Double ret = ACCEPTABLE_REFUSAL_RATE * 5 * ressources + ressources;
        return ret.intValue();
    }

}
