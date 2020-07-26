package shared;

import java.io.Serializable;

public class CatalogEntry implements Serializable{
    private String hostname;
    private int ressources;

    public CatalogEntry(String hostname, int ressources) {
        this.hostname = hostname;
        this.ressources = ressources;
    }

    public String getHostname() {
        return hostname;
    }

    public void setHostname(String hostname) {
        this.hostname = hostname;
    }

    public int getRessources() {
        return ressources;
    }

    public void setRessources(int ressources) {
        this.ressources = ressources;
    }

    @Override
    public String toString() {
        return "CatalogEntry{" +
                "hostname='" + hostname + '\'' +
                ", ressources=" + ressources +
                '}';
    }
}
