

import catalog.Catalog;
import shared.CatalogEntry;

import static org.junit.jupiter.api.Assertions.*;

class CatalogTest {
    private Catalog catalog = new Catalog();

    @org.junit.jupiter.api.Test
    void testCatalog() {
        try {
            String host = "catalin";
            int ressources = 5;
            String repartitor = "gab";
            String pass = "alol";
            catalog.registerHost(host, 5);
            for (CatalogEntry c : catalog.getHosts()){
                if(c.getHostname().equals(host)){
                    assert true;
                }
            }

            catalog.registerRepartitor(repartitor, pass);
            assertTrue(catalog.verifyRepartitor(repartitor, pass));

            assertTrue(true);
        }catch (Exception e){
            //
        }

    }

}
