package main.Model;

import java.io.IOException;
import java.util.Set;

/**
 * Users Interface
 */
public interface UsersInterface {
    /**
     * Method to get number of valid users
     * @return Number of valid users
     */
    int getNumberOfUsers();

    /**
     * Users cloner
     * @return Cloned catalogue
     */
    UsersInterface clone();

    /**
     * Method to check if a user exists given its ID
     * @param id ID to check
     * @return true if the user is in the catalog, false otherwise
     */
    boolean containsUser(String id);

    /**
     * Method to add an user to catalog
     * @param u User to add
     */
    void addUser(UserInterface u);

    /**
     * Method to get Users IDs
     * @return Set of Users IDs
     */
    Set<String> getUsersIDs();

    /**
     * Method to read users filer
     * @param filepath Path of the file to read
     * @throws IOException Exception to prevent IO errors
     */
    void readUsersFile(String filepath) throws IOException;
}
