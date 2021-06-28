package test.Users;

import main.Model.User;
import main.Model.UserInterface;
import main.Model.UsersInterface;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * Test class of a catalog of businesses on an Hash Map
 */
class UsersHashMap implements UsersInterface, Serializable {
    /**
     * Users Catalog
     */
    Map<String, UserInterface> usersCatalog;

    /**
     * Empty Constructor
     */
    public UsersHashMap(){
        this.usersCatalog = new HashMap<>();
    }

    /**
     * Copy Constructor
     * @param u Catalog to copy
     */
    public UsersHashMap(UsersHashMap u){
        this.setUsersCatalog(u.getUsersCatalog());
    }

    /**
     * Users cloner
     * @return Cloned catalogue
     */
    public UsersHashMap clone(){
        return new UsersHashMap(this);
    }

    /**
     * Method to get Users catalog
     * @return Users catalog
     */
    public Map<String, UserInterface> getUsersCatalog(){
        Map<String, UserInterface> ans = new HashMap<>();
        for(String s : this.usersCatalog.keySet())
            ans.put(s, this.usersCatalog.get(s).clone());
        return ans;
    }

    /**
     * Method to set users catalogue
     * @param u Catalog to set
     */
    public void setUsersCatalog(Map<String, UserInterface> u){
        this.usersCatalog = new HashMap<>();
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
        if(this.usersCatalog == null) this.usersCatalog = new HashMap<>();
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