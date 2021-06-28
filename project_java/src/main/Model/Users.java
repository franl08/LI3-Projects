package main.Model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.Hashtable;
import java.util.Set;

/**
 * Class to keep Users Catalog
 */
public class Users implements UsersInterface, Serializable {
    /**
     * Users Catalog
     */
    Hashtable<String, UserInterface> usersCatalog;

    /**
     * Empty Constructor
     */
    public Users(){
        this.usersCatalog = new Hashtable<>();
    }

    /**
     * Copy Constructor
     * @param u Catalog to copy
     */
    public Users(Users u){
        this.setUsersCatalog(u.getUsersCatalog());
    }

    /**
     * Users cloner
     * @return Cloned catalogue
     */
    public Users clone(){
        return new Users(this);
    }

    /**
     * Method to get Users catalog
     * @return Users catalog
     */
    public Hashtable<String, UserInterface> getUsersCatalog(){
        Hashtable<String, UserInterface> ans = new Hashtable<>();
        for(String s : this.usersCatalog.keySet())
            ans.put(s, this.usersCatalog.get(s).clone());
        return ans;
    }

    /**
     * Method to set users catalogue
     * @param u Catalog to set
     */
    public void setUsersCatalog(Hashtable<String, UserInterface> u){
        this.usersCatalog = new Hashtable<>();
        for(String s : u.keySet())
            this.usersCatalog.put(s, u.get(s).clone());
    }

    /**
     * Method to get number of valid users
     * @return Number of valid users
     */
    public int getNumberOfUsers(){
        return usersCatalog.size();
    }

    /**
     * Method to check if a user exists given its ID
     * @param id ID to check
     * @return true if the user is in the catalog, false otherwise
     */
    public boolean containsUser(String id){
        return usersCatalog.containsKey(id);
    }

    /**
     * Method to add an user to catalog
     * @param u User to add
     */
    public void addUser(UserInterface u){
        usersCatalog.put(u.getId(), u);
    }

    /**
     * Method to get Users IDs
     * @return Set of Users IDs
     */
    public Set<String> getUsersIDs(){
        return this.usersCatalog.keySet();
    }

    /**
     * Method to read users filer
     * @param filepath Path of the file to read
     * @throws IOException Exception to prevent IO errors
     */
    public void readUsersFile(String filepath) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filepath));
        String line;
        while((line = br.readLine()) != null) {
            String[] fields = line.split(";");
            if (fields.length == 3) {
                String userID = fields[0];
                String username = fields[1];
                String friends = fields[2];
                if(UserInterface.verifyID(userID)){
                    this.addUser(new User(userID, username));
                }
            }
        }

        br.close();
    }
}
