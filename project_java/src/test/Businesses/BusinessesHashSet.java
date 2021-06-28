package test.Businesses;

import main.Model.Business;
import main.Model.BusinessInterface;
import main.Model.BusinessesInterface;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * Test class of a catalog of businesses on an Hash Set
 */
class BusinessesHashSet implements BusinessesInterface {
    /**
     * Businesses Catalog
     */
    private HashSet<BusinessInterface> busisSet;

    /**
     * Empty Constructor
     */
    public BusinessesHashSet(){
        this.busisSet = new HashSet<>();
    }

    /**
     * Copy Constructor
     * @param b Catalog of Businesses to copy
     */
    public BusinessesHashSet(BusinessesHashSet b){
        this.setBusisSet(b.getBusisSet());
    }

    /**
     * Businesses setter
     * @param bs Catalog of businesses to set
     */
    public void setBusisSet(HashSet<BusinessInterface> bs){
        this.busisSet = new HashSet<>();
        for(BusinessInterface b : bs)
            this.busisSet.add(b.clone());
    }

    /**
     * Businesses getter
     * @return Catalog of businesses
     */
    public HashSet<BusinessInterface> getBusisSet(){
        HashSet<BusinessInterface> ans = new HashSet<>();
        for(BusinessInterface b : this.busisSet)
            ans.add(b.clone());
        return ans;
    }

    /**
     * Method to get current number of businesses on catalog
     * @return Number of businesses on catalog
     */
    public int getNumberOfBusinesses() {
        return busisSet.size();
    }

    /**
     * Method to check if the catalogue contains a business with the given ID
     * @param ID ID to check
     * @return true if it exists, false otherwise
     */
    public boolean containsBusiness(String ID) {
        for(BusinessInterface b : this.busisSet)
            if(b.getId().equals(ID)) return true;
        return false;
    }

    /**
     * Method to add a business to catalog
     * @param bi Business to add
     */
    public void addBusiness(BusinessInterface bi) {
        this.busisSet.add(bi.clone());
    }

    /**
     * Businesses Cloner
     * @return Cloned Catalog of Businesses
     */
    public BusinessesInterface clone() {
        return new BusinessesHashSet(this);
    }

    public Set<String> getBusinessesIDs() {
        Set<String> ans = new HashSet<>();
        for(BusinessInterface b : this.busisSet)
            ans.add(b.getId());
        return ans;
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
    public BusinessInterface getBusinessWithID(String ID) {
        for(BusinessInterface b : this.busisSet)
            if(b.getId().equals(ID)) return b.clone();
        return null;
    }

    /**
     * Method to get a Map associating Sets of Businesses IDs with their cities
     * @return Map associating Sets of Businesses IDs with their cities
     */
    public Map<String, Set<String>> getBusinessesByCity(){
        Map<String, Set<String>> ans = new HashMap<>();
        for(BusinessInterface b : this.busisSet) {
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
        for(BusinessInterface b : this.busisSet) {
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
        for(BusinessInterface b : this.busisSet){
            String s = b.getId();
            map.put(s, getBusinessWithID(s).getName());
        }
        return map;
    }
}
