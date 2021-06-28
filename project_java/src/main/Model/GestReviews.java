package main.Model;

import java.io.*;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Database Class
 */
public class GestReviews implements Serializable{
    /**
     * Database Businesses
     */
    private BusinessesInterface businesses;
    /**
     * Database users
     */
    private UsersInterface users;
    /**
     * Database reviews
     */
    private ReviewsInterface reviews;

    /**
     * Name of the last businesses file read
     */
    private String lastBusinessesFile;
    /**
     * Name of the last users file read
     */
    private String lastUsersFile;
    /**
     * Name of the last reviews file read
     */
    private String lastReviewsFile;

    /**
     * Number of invalid reviews read
     */
    private int invalidReviews;

    /**
     * Empty Constructor
     */
    public GestReviews(){
        this.businesses = new Businesses();
        this.users = new Users();
        this.reviews = new Reviews();
        this.lastBusinessesFile = "No businesses file read yet.";
        this.lastUsersFile = "No users file read yet.";
        this.lastReviewsFile = "No reviews file read yet.";
    }

    /**
     * Copy Constructor
     * @param g Database to copy
     */
    public GestReviews(GestReviews g){
        this.setBusinesses(g.getBusinesses());
        this.setUsers(g.getUsers());
        this.setReviews(g.getReviews());
        this.lastBusinessesFile = g.getLastBusinessesFile();
        this.lastUsersFile = g.getLastUsersFile();
        this.lastReviewsFile = g.getLastReviewsFile();
        this.invalidReviews = g.getInvalidReviews();
    }

    /**
     * Businesses getter
     * @return Businesses on database
     */
    public BusinessesInterface getBusinesses() {
        return this.businesses.clone();
    }

    /**
     * Businesses setter
     * @param businesses Businesses to set
     */
    public void setBusinesses(BusinessesInterface businesses) {
        this.businesses = businesses.clone();
    }

    /**
     * Users getter
     * @return Users on database
     */
    public UsersInterface getUsers() {
        return this.users.clone();
    }

    /**
     * Users setter
     * @param users Users to set
     */
    public void setUsers(UsersInterface users) {
        this.users = users.clone();
    }

    /**
     * Reviews getter
     * @return Reviews on database
     */
    public ReviewsInterface getReviews() {
        return this.reviews.clone();
    }

    /**
     * Reviews setter
     * @param reviews Reviews to set
     */
    public void setReviews(ReviewsInterface reviews) {
        this.reviews = reviews.clone();
    }

    /**
     * Method to get last Businesses file read name
     * @return Last Businesses file read name
     */
    public String getLastBusinessesFile() {
        return this.lastBusinessesFile;
    }

    /**
     * Method to set last Businesses file read name
     * @param lastBusinessesFile Last Businesses file read name
     */
    public void setLastBusinessesFile(String lastBusinessesFile) {
        this.lastBusinessesFile = lastBusinessesFile;
    }

    /**
     * Method to get last Users file read name
     * @return Last Users file read name
     */
    public String getLastUsersFile() {
        return this.lastUsersFile;
    }

    /**
     * Method to set last Users file read name
     * @param lastUsersFile Last Users file read name
     */
    public void setLastUsersFile(String lastUsersFile) {
        this.lastUsersFile = lastUsersFile;
    }

    /**
     * Method to get last Reviews file read name
     * @return Last Reviews file read name
     */
    public String getLastReviewsFile() {
        return this.lastReviewsFile;
    }

    /**
     * Method to set last Reviews file read name
     * @param lastReviewsFile Last Reviews file read name
     */
    public void setLastReviewsFile(String lastReviewsFile) {
        this.lastReviewsFile = lastReviewsFile;
    }

    /**
     * Method to set number of invalid reviews read
     * @param invalidReviews Invalid reviews read
     */
    public void setInvalidReviews(int invalidReviews) {
        this.invalidReviews = invalidReviews;
    }

    // Statistical Query 1 -> All the following methods

    /**
     * Method to get last files read
     * @return List with last files read
     */
    public List<String> getLastFilesRead(){
        List<String> ans = new ArrayList<>();
        ans.add(this.lastBusinessesFile);
        ans.add(this.lastUsersFile);
        ans.add(this.lastReviewsFile);
        return ans;
    }

    /**
     * Method to get number of invalid reviews read
     * @return Number of invalid reviews read
     */
    public int getInvalidReviews(){
        return this.invalidReviews;
    }

    /**
     * Method to get number of businesses read
     * @return Number of businesses read
     */
    public int getTotalBusinesses(){
        return this.businesses.getNumberOfBusinesses();
    }

    /**
     * Method to get number of businesses reviewed
     * @return Number of businesses reviewed
     */
    public int getTotalBusinessesReviewed(){
        return this.reviews.getNumberOfBusinessesReviewed();
    }

    /**
     * Method to get number of businesses not reviewed
     * @return Number of businesses not reviewed
     */
    public int getTotalBusinessesNotReviewed(){
        return getTotalBusinesses() - getTotalBusinessesReviewed();
    }

    /**
     * Method to get number of total users
     * @return Number of total users
     */
    public int getTotalUsers(){
        return this.users.getNumberOfUsers();
    }

    /**
     * Method to get number of total users with reviews
     * @return Number of total users with reviews
     */
    public int getTotalUsersWithReviews(){
        return this.reviews.getNumberOfUsersWithReviews();
    }

    /**
     * Method to get number of total users with reviews
     * @return Number of total users without reviews
     */
    public int getTotalUsersWithoutReviews(){
        return this.reviews.getNumberOfReviews() - getTotalUsersWithReviews();
    }

    /**
     * Method to get number of reviews without impact
     * @return Number of reviews without impact
     */
    public int getTotalReviewsWithoutImpact(){
        return this.reviews.getNumberOfReviewsWithoutImpact();
    }
    // End of Statistical Query 1

    // Statistical Query 2

    /**
     * Method to get Map associating months with number of reviews done in each month
     * @return Map associating months with number of reviews done in each month
     */
    public Map<Integer, Integer> getNReviewsPerMonth(){
        return this.reviews.getNumberOfReviewsPerMonth();
    }

    /**
     * Method to get a pair containing global reviews average and a map associating months with review's average in each month
     * @return Pair containing global reviews average and a map associating months with review's average in each month
     */
    public Map.Entry<Float, Map<Integer, Float>> getAverageClassificationPerMonthAndGlobal(){
        return new AbstractMap.SimpleEntry<>(this.reviews.getGlobalAverage(), this.reviews.getAveragePerMonth());
    }

    /**
     * Method to get a Map associating months with the numbers of different users who reviewed a business in that month
     * @return Map associating months with the numbers of different users who reviewed a business in that month
     */
    public Map<Integer, Integer> getDifferentUsersPerMonth(){
        return this.reviews.getDifferentUsersPerMonth();
    }
    // End of Statistical Query 2

    /**
     * Method to read Reviews File
     * @param filepath Reviews file path to read
     * @throws IOException Exception to prevent IO errors
     */
    public void readReviewsFile(String filepath) throws IOException {
        this.setLastReviewsFile(filepath);
        BufferedReader br = new BufferedReader(new FileReader(filepath));
        String line = br.readLine();
        while((line = br.readLine()) != null) {
            String[] fields = line.split(";");
            if (fields.length == 9) {
                String id = fields[0];
                String uID = fields[1];
                String bID = fields[2];
                float stars = Float.parseFloat(fields[3]);
                int useful = Integer.parseInt(fields[4]);
                int funny = Integer.parseInt(fields[5]);
                int cool = Integer.parseInt(fields[6]);
                String dateString = fields[7];
                String text = fields[8];
                if(ReviewInterface.verifyID(id) && this.businesses.containsBusiness(bID) && this.users.containsUser(uID)){
                    String[] splitDate = dateString.split(" ");
                    if(splitDate.length == 2){
                        String[] elemsOfDay = splitDate[0].split("-");
                        String[] elemsOfHour = splitDate[1].split(":");
                        if(elemsOfDay.length == 3 && elemsOfHour.length == 3){
                            LocalDateTime date = LocalDateTime.of(Integer.parseInt(elemsOfDay[0]), Integer.parseInt(elemsOfDay[1]), Integer.parseInt(elemsOfDay[2]),
                                    Integer.parseInt(elemsOfHour[0]), Integer.parseInt(elemsOfHour[1]), Integer.parseInt(elemsOfHour[2]));
                            this.reviews.addReview(new Review(id, uID, bID, stars, useful, funny, cool, date, text));
                        }
                        else this.invalidReviews++;
                    }
                    else this.invalidReviews++;
                }
                else this.invalidReviews++;
            }
            else this.invalidReviews++;
        }

        br.close();
    }

    /**
     * Method to read users file
     * @param filepath Path to the file to read
     * @throws IOException Exception to prevent IO errors
     */
    public void readUsersFile(String filepath) throws IOException {
        this.setLastUsersFile(filepath);
        this.users.readUsersFile(filepath);
    }

    /**
     * Method to read businesses file
     * @param filepath Path to the file to read
     * @throws IOException Exception to prevent IO errors
     */
    public void readBusinessesFile(String filepath) throws IOException{
        this.setLastBusinessesFile(filepath);
        this.businesses.readBusinessesFile(filepath);
    }

    /**
     * Method to save current state of database as Object
     * @param fileName Name of the file to save current state of database as Object
     * @throws IOException Exception to prevent IO error
     */
    public void saveGestReviewsObject(String fileName) throws IOException{
        String filePath = "saves/" + fileName + ".dat";
        File save = new File(filePath);
        if(!save.exists()) save.createNewFile();
        BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(save));
        ObjectOutputStream oos = new ObjectOutputStream(bos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }

    /**
     * Method to save current state of database as Object on default path
     * @throws IOException Exception to prevent IO errors
     */
    public void saveGestReviewsObject() throws IOException{
        saveGestReviewsObject("gestReviews");
    }

    /**
     * Method to read object file containing database
     * @param fileName Name of the file to read
     * @return New Database
     * @throws IOException Exception to prevent IO errors
     * @throws ClassNotFoundException Exception to prevent writing on undefined classes
     */
    public GestReviews readGestReviewsObject(String fileName) throws IOException, ClassNotFoundException {
        String filePath = "saves/" + fileName;
        FileInputStream fis = new FileInputStream(filePath);
        ObjectInputStream ois = new ObjectInputStream(fis);
        GestReviews g = (GestReviews) ois.readObject();
        ois.close();
        return g;
    }

    /**
     * Query 1
     * @return List containing Ids of reviewed businesses
     */
    public List<String> getReviewedBusinesses() {
        Set<String> revs = this.reviews.businessesReviewed();
        Set<String> busis = this.businesses.getBusinessesIDs();
        return busis.stream().filter(b -> !(revs.contains(b))).sorted().collect(Collectors.toList());
    }

    /**
     * Query 2
     * @param month Month to get reviews of
     * @param year Year to get reviews of
     * @return Pair containing month and year of reviews
     */
    public Query2Pair reviewsByMonth(int month, int year){
        return this.reviews.query2(month, year);
    }

    /**
     * Query 3
     * @param userID User ID to check
     * @return Map containing, for each month, how many reviews the user did, how many different businesses reviewed and the average grade
     */
    public Map<Integer, Query3Triple> distinctReviewsUserByMonth(String userID){
        return this.reviews.query3(userID);
    }

    /**
     * Query 4
     * @param businessID Business ID to check
     * @return Map containing, month by month, how many times the business was reviewed, by how many different users and the average grade
     */
    public Map<Integer, Query4Triple> distinctReviewsBusinessByMonth(String businessID){
        return this.reviews.query4(businessID);
    }

    /**
     * Query 5
     * @param userID User ID to check
     * @return List of business names that the user rated the most and (how many), sorted in descending order of quantity and, for equal quantities, in alphabetical order of business
     */
    public List<Map.Entry<String, Integer>> getUserMostReviewedBusinesses(String userID){
        Map<String, String> idsAndNames = this.businesses.busisIDsWithNames();
        return this.reviews.query5(userID, idsAndNames);
    }

    /**
     * Query 6
     * @param n Wanted limit
     * @return Set of X most rated businesses (with more reviews) each year, indicating the total number of distinguished users who rated it
     */
    public Map<Integer, List<Map.Entry<String, Long>>> mostReviewedBusinesses(int n){
        return this.reviews.query6(n);
    }

    /**
     * Query 7
     * @return Map containing, city by city, the list of the three most famous businesses in terms of total reviews
     */
    public Map<String, List<String>> top3BusisByCity(){
        Map<String, Set<String>> busisByCity = this.businesses.getBusinessesByCity();
        return this.reviews.query7(busisByCity);
    }

    /**
     * Query 8
     * @param n Wanted limit
     * @return Codes of the X users who evaluated the most different deals, indicating how many, with the ordering criterion being the descending order of the number of deals
     */
    public List<Map.Entry<String, Long>> moreActiveUsers(int n){
        return this.reviews.query8(n);
    }

    /**
     * Query 9
     * @param businessID Business ID to check
     * @param n Wanted Limit
     * @return Set of n users who evaluated the business the most and, for each one, what is the average value of business classification;
     */
    public List<Map.Entry<String, Float>> usersWithMoreReviewsOnBusiness(String businessID, int n){
        return this.reviews.query9(businessID, n);
    }

    /**
     * Query 10
     * @return For each state, city to city, the average rating of each business.
     */
    public Map<String, Map<String, Map<String, Float>>> businessesByStateCityWithAverage(){
        Map<String, Map<String, Set<String>>> busisInStatesAndCities = this.businesses.getBusinessesByStateAndCity();
        return this.reviews.query10(busisInStatesAndCities);
    }
}
