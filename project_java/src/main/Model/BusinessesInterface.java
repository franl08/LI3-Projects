package main.Model;

import java.io.IOException;
import java.util.Map;
import java.util.Set;

/**
 * Businesses Interface
 */
public interface BusinessesInterface {

    /**
     * Method to get current number of businesses on catalog
     * @return Number of businesses on catalog
     */
    int getNumberOfBusinesses();

    /**
     * Method to check if the catalogue contains a business with the given ID
     * @param ID ID to check
     * @return true if it exists, false otherwise
     */
    boolean containsBusiness(String ID);

    /**
     * Method to add a business to catalog
     * @param b Business to add
     */
    void addBusiness(BusinessInterface b);

    /**
     * Businesses Cloner
     * @return Cloned Catalog of Businesses
     */
    BusinessesInterface clone();

    /**
     * Method to get a Set of the current businesses on catalogue IDs
     * @return Set of IDs
     */
    Set<String> getBusinessesIDs();

    /**
     * Method to read businesses file
     * @param filepath File to read
     * @throws IOException Exception to prevent IO errors
     */
    void readBusinessesFile(String filepath) throws IOException;

    /**
     * Method to get a business given its id
     * @param ID ID to search for
     * @return Business with the given ID
     */
    BusinessInterface getBusinessWithID(String ID);

    /**
     * Method to get a Map associating Sets of Businesses IDs with their cities
     * @return Map associating Sets of Businesses IDs with their cities
     */
    Map<String, Set<String>> getBusinessesByCity();

    /**
     * Method to get a Map associating Businesses States with a Map associating Sets of Businesses IDs with their cities
     * @return Map associating Businesses States with a Map associating Sets of Businesses IDs with their cities
     */
    Map<String, Map<String, Set<String>>> getBusinessesByStateAndCity();

    /**
     * Method to get a Map associating Businesses IDs with their names
     * @return Map associating Businesses IDs with their names
     */
    Map<String, String> busisIDsWithNames();
}
