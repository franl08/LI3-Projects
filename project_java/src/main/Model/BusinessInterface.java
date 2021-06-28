package main.Model;

/**
 * Business Interface
 */
public interface BusinessInterface {
    /**
     * ID getter
     * @return Business's ID
     */
    String getId();

    /**
     * Name getter
     * @return Business's name
     */
    String getName();

    /**
     * State getter
     * @return Business's State
     */
    String getState();

    /**
     * City getter
     * @return Business's City
     */
    String getCity();

    /**
     * Business cloner
     * @return Cloned Business
     */
    BusinessInterface clone();

    /**
     * Method to validate an ID
     * @param ID ID to check
     * @return true if ID is valid, false otherwise
     */
    static boolean verifyID(String ID){
        return ID.length() == 22;
    }
}
