package main.Model;

/**
 * User Interface
 */
public interface UserInterface {
    /**
     * ID getter
     * @return User ID
     */
    String getId();

    /**
     * Name getter
     * @return User Name
     */
    String getName();

    /**
     * User cloner
     * @return Cloned User
     */
    User clone();

    /**
     * Method to validate an ID
     * @param id ID to check
     * @return true if ID is valid, false otherwise
     */
    static boolean verifyID(String id){
        return id.length() == 22;
    }
}
