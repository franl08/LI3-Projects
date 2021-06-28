package test.Businesses;

import main.Model.Business;
import main.Model.BusinessInterface;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Test class of a catalog of businesses on an Hash Map
 */
class BusinessesHashMap {
    /**
     * Businesses Catalog
     */
    public Map<String, BusinessInterface> businessesCatalog;

    /**
     * Empty Constructor
     */
    public BusinessesHashMap(){
        this.businessesCatalog = new HashMap<>();
    }

    /**
     * Copy Constructor
     * @param b Catalog of Businesses to copy
     */
    public BusinessesHashMap(BusinessesHashMap b){
        this.setBusinessesCatalog(b.getBusinessesCatalog());
    }

    /**
     * Businesses Cloner
     * @return Cloned Catalog of Businesses
     */
    public BusinessesHashMap clone(){
        return new BusinessesHashMap(this);
    }

    /**
     * Businesses getter
     * @return Catalog of businesses
     */
    public HashMap<String, BusinessInterface> getBusinessesCatalog(){
        HashMap<String, BusinessInterface> ans = new HashMap<>();
        for(String s : this.businessesCatalog.keySet())
            ans.put(s, this.businessesCatalog.get(s).clone());
        return ans;
    }

    /**
     * Businesses setter
     * @param m Catalog of businesses to set
     */
    public void setBusinessesCatalog(HashMap<String, BusinessInterface> m){
        this.businessesCatalog = new HashMap<>();
        for(String s : m.keySet())
            this.businessesCatalog.put(s, m.get(s).clone());
    }

    /**
     * Method to get current number of businesses on catalog
     * @return Number of businesses on catalog
     */
    public int getNumberOfBusinesses(){
        return this.businessesCatalog.size();
    }

    /**
     * Method to check if the catalogue contains a business with the given ID
     * @param ID ID to check
     * @return true if it exists, false otherwise
     */
    public boolean containsBusiness(String ID){
        return this.businessesCatalog.containsKey(ID);
    }

    /**
     * Method to add a business to catalog
     * @param b Business to add
     */
    public void addBusiness(BusinessInterface b){
        this.businessesCatalog.put(b.getId(), b);
    }

    /**
     * Method to get a Set of the current businesses on catalogue IDs
     * @return Set of IDs
     */
    public Set<String> getBusinessesIDs(){
        return this.businessesCatalog.keySet();
    }

    /**
     * Method to read businesses file
     * @param filepath File to read
     * @throws IOException Exception to prevent IO errors
     */
    public void readBusinessesFile(String filepath) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filepath));
        String line;
        while((line = br.readLine()) != null) {
            String[] fields = line.split(";");
            if (fields.length == 5) {
                String id = fields[0];
                String name = fields[1];
                String city = fields[2];
                String state = fields[3];
                String categories = fields[4];
                if(BusinessInterface.verifyID(id)){
                    Business b = new Business(id, name, city, state, categories);
                    this.addBusiness(b);
                }
            }
        }

        br.close();
    }

    /**
     * Method to get a business given its id
     * @param ID ID to search for
     * @return Business with the given ID
     */
    public BusinessInterface getBusinessWithID(String ID){
        return this.businessesCatalog.get(ID).clone();
    }

    /**
     * Method to get a Map associating Sets of Businesses IDs with their cities
     * @return Map associating Sets of Businesses IDs with their cities
     */
    public Map<String, Set<String>> getBusinessesByCity(){
        Map<String, Set<String>> ans = new HashMap<>();
        for(BusinessInterface b : this.businessesCatalog.values()) {
            if (ans.containsKey(b.getCity())) ans.get(b.getCity()).add(b.getId());
            else{
                Set<String> toAdd = new HashSet<>();
                toAdd.add(b.getId());
                ans.put(b.getCity(), toAdd);
            }
        }
        return ans;
    }

    /**
     * Method to get a Map associating Businesses States with a Map associating Sets of Businesses IDs with their cities
     * @return Map associating Businesses States with a Map associating Sets of Businesses IDs with their cities
     */
    public Map<String, Map<String, Set<String>>> getBusinessesByStateAndCity(){
        Map<String, Map<String, Set<String>>> ans = new HashMap<>();
        for(BusinessInterface b : this.businessesCatalog.values()) {
            if (ans.containsKey(b.getState())) {
                Map<String, Set<String>> busisInCities = ans.get(b.getState());
                if (busisInCities.containsKey(b.getCity())) busisInCities.get(b.getCity()).add(b.getId());
                else {
                    Set<String> toAdd = new HashSet<>();
                    toAdd.add(b.getId());
                    busisInCities.put(b.getCity(), toAdd);
                }
            } else {
                Map<String, Set<String>> mapToAdd = new HashMap<>();
                Set<String> toAdd = new HashSet<>();
                toAdd.add(b.getId());
                mapToAdd.put(b.getCity(), toAdd);
                ans.put(b.getState(), mapToAdd);
            }
        }
        return ans;
    }

    /**
     * Method to get a Map associating Businesses IDs with their names
     * @return Map associating Businesses IDs with their names
     */
    public Map<String, String> busisIDsWithNames(){
        Map<String, String> map = new HashMap<>();
        for(String s : this.businessesCatalog.keySet()){
            map.put(s, getBusinessWithID(s).getName());
        }
        return map;
    }
}
