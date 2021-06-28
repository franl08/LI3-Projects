package main.Model;

import java.io.Serializable;

/**
 * User Class
 */
public class User implements UserInterface, Serializable {
    /**
     * User ID
     */
    private final String id;
    /**
     * User Name
     */
    private final String name;

    /**
     * Parametrized Constructor
     * @param id User ID
     * @param name User name
     */
    public User(String id, String name){
        this.id = id;
        this.name = name;
    }

    /**
     * Copy Constructor
     * @param u User to copy
     */
    public User(User u){
        this.id = u.getId();
        this.name = u.getName();
    }

    /**
     * User cloner
     * @return Cloned User
     */
    public User clone(){
        return new User(this);
    }

    /**
     * ID getter
     * @return User ID
     */
    public String getId() {
        return this.id;
    }

    /**
     * Name getter
     * @return User Name
     */
    public String getName() {
        return this.name;
    }

}
