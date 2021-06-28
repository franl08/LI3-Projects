package main;

import main.Controller.Controller;

/**
 * Class to run the app
 */
public class GestReviewsAppMVC {
    /**
     * Main function to run the app
     * @param args Arguments of main function
     */
    public static void main(String[] args){
        Controller controller = new Controller();
        controller.run();
    }
}
