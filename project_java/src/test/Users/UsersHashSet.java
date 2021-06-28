package test.Users;

import main.Model.User;
import main.Model.UserInterface;
import main.Model.UsersInterface;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

/**
 * Test class of a catalog of businesses on an Hash Set
 */
class UsersHashSet implements UsersInterface {
    /**
     * Users Catalog
     */
    private HashSet<UserInterface> usersSet;

    /**
     * Empty Constructor
     */
    public UsersHashSet(){
        this.usersSet = new HashSet<>();
    }

    /**
     * Copy Constructor
     * @param u Catalog to copy
     */
    public UsersHashSet(UsersHashSet u){
        this.setUsersSet(u.getUsersSet());
    }

    /**
     * Method to set users catalogue
     * @param u Catalog to set
     */
    public void setUsersSet(Set<UserInterface> u){
        this.usersSet = new HashSet<>();
        for(UserInterface us : u)
            this.usersSet.add(us.clone());
    }

    /**
     * Method to get Users catalog
     * @return Users catalog
     */
    public Set<UserInterface> getUsersSet(){
        Set<UserInterface> ans = new HashSet<>();
        for(UserInterface u : this.usersSet)
            ans.add(u.clone());
        return ans;
    }

    /**
     * Method to get number of valid users
     * @return Number of valid users
     */
    public int getNumberOfUsers() {
        return this.usersSet.size();
    }

    /**
     * Users cloner
     * @return Cloned catalogue
     */
    public UsersInterface clone() {
        return new UsersHashSet(this);
    }


    /**
     * Method to check if a user exists given its ID
     * @param id ID to check
     * @return true if the user is in the catalog, false otherwise
     */
    public boolean containsUser(String id) {
        for(UserInterface u : this.usersSet)
            if(u.getId().equals(id)) return true;
        return false;
    }

    /**
     * Method to add an user to catalog
     * @param u User to add
     */
    public void addUser(UserInterface u) {
        this.usersSet.add(u.clone());
    }

    /**
     * Method to get Users IDs
     * @return Set of Users IDs
     */
    public Set<String> getUsersIDs() {
        Set<String> ans = new HashSet<>();
        for(UserInterface u : this.usersSet)
            ans.add(u.getId());
        return ans;
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
