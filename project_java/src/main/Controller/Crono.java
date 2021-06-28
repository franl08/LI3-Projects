package main.Controller;

import static java.lang.System.nanoTime;

/**
 * Class to generate timers
 */
public class Crono {
    /**
     * Timer begin
     */
    private static long begin = 0L;
    /**
     * Timer end
     */
    private static long end = 0L;

    /**
     * Method to start timer
     */
    public static void start() {
        end = 0L;
        begin = nanoTime();
    }

    /**
     * Method to stop timer
     * @return Elapsed time
     */
    public static double stop() {
        end = nanoTime();
        long elapsedTime = end - begin;
        return elapsedTime / 1.0E09;
    }

    /**
     * Method to get time as String
     * @return String of elapsed time
     */
    public static String getTimeAsString() {
        return "" + stop();
    }

    /**
     * Method to print elapsed time
     */
    public static void printElapsedTime() {
        System.out.println( "Elapsed Time: " + stop() + " s");
    }
}