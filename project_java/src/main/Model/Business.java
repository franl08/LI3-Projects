package main.Model;

import java.io.Serializable;

/**
 * Class for a Business
 */
public class Business implements BusinessInterface, Serializable{
    /**
     * Business ID
     */
    private final String id;
    /**
     * Business Name
     */
    private final String name;
    /**
     * Business City
     */
    private final String city;
    /**
     * Business State
     */
    private final String state;
    /**
     * Business Categories
     */
    private final String categories;

    /**
     * Parametrized Constructor
     * @param id Business's ID
     * @param name Business's Name
     * @param city Business's City
     * @param state Business's State
     * @param categories Business's Categories
     */
    public Business(String id, String name, String city, String state, String categories){
        this.id = id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories;
    }

    /**
     * Copy Constructor
     * @param b Business to Copy
     */
    public Business(Business b){
        this.id = b.getId();
        this.name = b.getName();
        this.city = b.getCity();
        this.state = b.getState();
        this.categories = b.getCategories();
    }

    /**
     * Business cloner
     * @return Cloned Business
     */
    public Business clone(){
        return new Business(this);
    }

    /**
     * ID getter
     * @return Business's ID
     */
    public String getId() {
        return this.id;
    }

    /**
     * Name getter
     * @return Business's name
     */
    public String getName() {
        return this.name;
    }

    /**
     * City getter
     * @return Business's City
     */
    public String getCity() {
        return this.city;
    }

    /**
     * State getter
     * @return Business's State
     */
    public String getState() {
        return this.state;
    }

    /**
     * Categories getter
     * @return Business's Categories
     */
    public String getCategories() {
        return this.categories;
    }

}
