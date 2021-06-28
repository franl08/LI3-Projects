package test.Reviews;

import main.Model.*;

import java.util.*;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.groupingBy;

/**
 * Test class of a catalog of reviews on an Hash Set
 */
class ReviewsHashSet implements ReviewsInterface {
    /**
     * Reviews Catalog
     */
    public HashSet<ReviewInterface> reviewsSet;

    /**
     * Empty Constructor
     */
    public ReviewsHashSet(){
        this.reviewsSet = new HashSet<>();
    }

    /**
     * Copy Constructor
     * @param r Catalog to copy
     */
    public ReviewsHashSet(ReviewsHashSet r){
        this.setReviewsSet(r.getReviewsSet());
    }

    /**
     * Reviews Catalog Setter
     * @param r Reviews Catalog to set
     */
    public void setReviewsSet(HashSet<ReviewInterface> r){
        this.reviewsSet = new HashSet<>();
        for(ReviewInterface rev : r)
            this.reviewsSet.add(rev.clone());
    }

    /**
     * Reviews Catalog getter
     * @return Reviews Catalog
     */
    public HashSet<ReviewInterface> getReviewsSet(){
        HashSet<ReviewInterface> ans = new HashSet<>();
        for(ReviewInterface r : this.reviewsSet)
            ans.add(r.clone());
        return ans;
    }

    /**
     * Method to get number of reviews
     * @return Number of reviews
     */
    public int getNumberOfReviews() {
        return this.reviewsSet.size();
    }

    /**
     * Method to check if the catalog contains a review given its ID
     * @param ID ID to check
     * @return true if it exists, false otherwise
     */
    public boolean existsReview(String ID) {
        for(ReviewInterface r : reviewsSet)
            if(r.getBusiness_ID().equals(ID)) return true;
        return false;
    }

    /**
     * Method to add a review to reviews catalog
     * @param r Review to add
     */
    public void addReview(ReviewInterface r) {
        this.reviewsSet.add(r);
    }

    /**
     * Cloner method
     * @return Cloned catalog
     */
    public ReviewsHashSet clone() {
        return new ReviewsHashSet(this);
    }

    /**
     * Method to get number of businesses reviewed
     * @return Number of businesses reviewed
     */
    public int getNumberOfBusinessesReviewed() {
        return businessesReviewed().size();
    }

    /**
     * Method to get Set of businesses IDs with reviews
     * @return Set of businesses IDs with reviews
     */
    public Set<String> businessesReviewed() {
        Set<String> busisIds = new HashSet<>();
        for(ReviewInterface r : this.reviewsSet)
            busisIds.add(r.getBusiness_ID());
        return busisIds;
    }

    /**
     * Method to get number of users with reviews
     * @return Number of users with reviews
     */
    public int getNumberOfUsersWithReviews() {
        Set<String> userIds = new HashSet<>();
        for(ReviewInterface r : this.reviewsSet)
            userIds.add(r.getUser_ID());
        return userIds.size();
    }

    /**
     * Method to get number of reviews without impact
     * @return Number of reviews without impact
     */
    public int getNumberOfReviewsWithoutImpact() {
        int total = 0;
        for(ReviewInterface r : this.reviewsSet)
            if(r.getCool() + r.getFunny() + r.getUseful() == 0) total++;
        return total;
    }

    /**
     * Method to get a Map associating months with number of reviews of that month
     * @return Map associating months with number of reviews of that month
     */
    public Map<Integer, Integer> getNumberOfReviewsPerMonth() {
        Map<Integer, Integer> ans = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            if(ans.containsKey(r.getMonthNumber()))
                ans.put(r.getMonthNumber(), ans.get(r.getMonthNumber()) + 1);
            else ans.put(r.getMonthNumber(), 1);
        }
        return ans;
    }

    /**
     * Method to get reviews average grade
     * @return Reviews average grade
     */
    public Float getGlobalAverage() {
        float totClass = 0;
        int ac = 0;
        for(ReviewInterface r : this.reviewsSet){
            totClass += r.getStars();
            ac++;
        }
        return totClass / ac;
    }

    /**
     * Method to get a Map associating months with the average grade of that month
     * @return Map associating months with the average grade of that month
     */
    public Map<Integer, Float> getAveragePerMonth() {
        Map<Integer, Float> ans = new HashMap<>();
        Map<Integer, Map.Entry<Integer, Float>> tmp = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            if(tmp.containsKey(r.getMonthNumber())){
                Map.Entry<Integer, Float> me = new AbstractMap.SimpleEntry<>(tmp.get(r.getMonthNumber()).getKey() + 1, tmp.get(r.getMonthNumber()).getValue() + r.getStars());
                tmp.put(r.getMonthNumber(), me);
            }
            else{
                Map.Entry<Integer, Float> me = new AbstractMap.SimpleEntry<>(1, r.getStars());
                tmp.put(r.getMonthNumber(), me);
            }
        }
        for(Integer i : tmp.keySet())
            ans.put(i, tmp.get(i).getValue() / tmp.get(i).getKey());
        return ans;
    }

    /**
     * Method to get a Map associating months with the number of distinct users who made reviews in that month
     * @return Map associating months with the number of distinct users who made reviews in that month
     */
    public Map<Integer, Integer> getDifferentUsersPerMonth() {
        Map<Integer, Set<String>> tmp = new HashMap<>();
        Map<Integer, Integer> ans = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            if(tmp.containsKey(r.getMonthNumber())) tmp.get(r.getMonthNumber()).add(r.getUser_ID());
            else{
                Set<String> users = new HashSet<>();
                users.add(r.getUser_ID());
                tmp.put(r.getMonthNumber(), users);
            }
        }
        for(Integer i : tmp.keySet())
            ans.put(i, tmp.get(i).size());
        return ans;
    }

    /**
     * Method to get list of Reviews on the given month and year
     * @param month Month
     * @param year Year
     * @return List of Reviews on the given month and year
     */
    public List<Review> getRevsInMonthAndYear(int month, int year){
        List<Review> ans = new ArrayList<>();
        for(ReviewInterface r : this.reviewsSet)
            if(r.getDate().getMonthValue() == month && r.getDate().getYear() == year) ans.add(r.clone());
        return ans;
    }

    /**
     * Auxiliary method to get query 2
     * @param month Month
     * @param year Year
     * @return Query 2 answer
     */
    public Query2Pair query2(int month, int year) {
        List<Review> listFilteredReviews = this.getRevsInMonthAndYear(month, year);
        return new Query2Pair(listFilteredReviews.size(), (int)listFilteredReviews.stream().map(ReviewInterface::getUser_ID).distinct().count());
    }

    /**
     * Method to get a list of Reviews made by the given user ID
     * @param userID User ID to check
     * @return List of Reviews made by the given user ID
     */
    public List<ReviewInterface> getRevsByUser(String userID){
        List<ReviewInterface> ans = new ArrayList<>();
        for(ReviewInterface r : this.reviewsSet)
            if(r.getUser_ID().equals(userID)) ans.add(r.clone());
        return ans;
    }

    /**
     * Auxiliary method to get query 3
     * @param user User ID
     * @return Query 3 answer
     */
    public Map<Integer, Query3Triple> query3(String user) {
        List<ReviewInterface> reviewsList = getRevsByUser(user);
        Map<Integer, List<ReviewInterface>> mapMonthsRevs = reviewsList.stream().collect(groupingBy(ReviewInterface::getMonthNumber));
        Map<Integer, Query3Triple> mapMonthTriple = new HashMap<>();
        for(Map.Entry<Integer, List<ReviewInterface>> e : mapMonthsRevs.entrySet()){
            int month = e.getKey();
            List<ReviewInterface> listRevs = e.getValue();
            int numberOfRevs = listRevs.size();
            int numberOfDistinctBusis = (int)listRevs.stream().map(ReviewInterface::getBusiness_ID).distinct().count();
            float totalClass = listRevs.stream().map(ReviewInterface::getStars).reduce((float) 0, Float::sum);
            float average = totalClass / numberOfRevs;
            Query3Triple q = new Query3Triple(numberOfRevs, numberOfDistinctBusis, average);
            mapMonthTriple.put(month, q);
        }
        return mapMonthTriple;
    }

    /**
     * Method to get a list of Reviews on the given business ID
     * @param businessID Business ID to check
     * @return List of Reviews on the given business ID
     */
    public List<ReviewInterface> getRevsInBusiness(String businessID){
        List<ReviewInterface> ans = new ArrayList<>();
        for(ReviewInterface r : this.reviewsSet)
            if(r.getBusiness_ID().equals(businessID)) ans.add(r.clone());
        return ans;
    }

    /**
     * Auxiliary method to get query 4
     * @param businessID Business ID
     * @return Query 4 answer
     */
    public Map<Integer, Query4Triple> query4(String businessID) {
        List<ReviewInterface> reviewsList = getRevsInBusiness(businessID);
        Map<Integer, List<ReviewInterface>> mapMonthsRevs = reviewsList.stream()
                .collect(groupingBy(ReviewInterface::getMonthNumber));
        Map<Integer, Query4Triple> mapMonthTriple = new HashMap<>();
        for(Map.Entry<Integer, List<ReviewInterface>> e : mapMonthsRevs.entrySet()){
            int month = e.getKey();
            List<ReviewInterface> listRevs = e.getValue();
            int numberOfRevs = listRevs.size();
            int numberOfDistinctUsers = (int) listRevs.stream().map(ReviewInterface::getUser_ID).distinct().count();
            float totalClass = listRevs.stream().map(ReviewInterface::getStars).reduce((float) 0, Float::sum);
            float average = totalClass / numberOfRevs;
            Query4Triple q = new Query4Triple(numberOfRevs, numberOfDistinctUsers, average);
            mapMonthTriple.put(month, q);
        }
        return mapMonthTriple;
    }

    /**
     * Auxiliary method to get query 5
     * @param userID User ID
     * @param idsAndNames Map associating businesses IDs with businesses names
     * @return Query 5 answer
     */
    public List<Map.Entry<String, Integer>> query5(String userID, Map<String, String> idsAndNames){
        Map<String, Integer> auxMap = new HashMap<>();

        for(ReviewInterface e : this.reviewsSet){
            if(e.getUser_ID().equals(userID)){
                String busID = e.getBusiness_ID();
                String bName = idsAndNames.get(busID);
                if(auxMap.containsKey(bName)) auxMap.put(bName, auxMap.get(bName) + 1);
                else auxMap.put(bName, 1);
            }
        }
        List<Map.Entry<String, Integer>> ans = new ArrayList<>(auxMap.entrySet());
        return ans.stream().sorted((a, b) -> b.getValue() - a.getValue()).collect(Collectors.toList());
    }

    /**
     * Method to get reviews per year
     * @return Map associating list of reviews with years
     */
    public Map<Integer, List<String>> getReviewsPerYear(){
        Map<Integer, List<String>> ans = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            if(ans.get(r.getDate().getYear()) == null){
                List<String> toAdd = new ArrayList<>();
                toAdd.add(r.getBusiness_ID());
                ans.put(r.getDate().getYear(), toAdd);
            }
            else ans.get(r.getDate().getYear()).add(r.getBusiness_ID());
        }
        return ans;
    }

    /**
     * Method to get Map associating businesses IDs with reviews IDs
     * @return Map associating businesses IDs with reviews IDs
     */
    public Map<String, List<String>> getMapBusinessesReviewsIDs(){
        Map<String, List<String>> ans = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            if(ans.containsKey(r.getBusiness_ID())) ans.get(r.getBusiness_ID()).add(r.getReview_ID());
            else{
                List<String> toAdd = new ArrayList<>();
                toAdd.add(r.getReview_ID());
                ans.put(r.getBusiness_ID(), toAdd);
            }
        }
        return ans;
    }

    /**
     * Auxiliary method to get query 6
     * @param lim Number of asked parameters
     * @return Query 6 answer
     */
    public Map<Integer, List<Map.Entry<String, Long>>> query6(int lim){
        Map<Integer, List<Map.Entry<String, Long>>> ans = new HashMap<>();
        Map<Integer, List<String>> reviewsPerYear = getReviewsPerYear();
        Map<String, List<String>> businessWithRevsIDs = getMapBusinessesReviewsIDs();
        for(Integer i : reviewsPerYear.keySet()){
            List<String> auxList = reviewsPerYear.get(i);
            Map<String, Integer> bIDsAndNumberOfOccurrences = new TreeMap<>();
            for(String s : auxList){
                if(bIDsAndNumberOfOccurrences.containsKey(s)){
                    bIDsAndNumberOfOccurrences.put(s, bIDsAndNumberOfOccurrences.get(s) + 1);
                }
                else bIDsAndNumberOfOccurrences.put(s, 1);
            }
            for(int k = 0; k < lim; k++){
                String max = null;
                int maxOcs = 0;
                for(String s : bIDsAndNumberOfOccurrences.keySet())
                    if(bIDsAndNumberOfOccurrences.get(s) > maxOcs){
                        max = s;
                        maxOcs = bIDsAndNumberOfOccurrences.get(s);
                    }
                if(max != null){
                    List<String> revsInBusiness = businessWithRevsIDs.get(max);
                    Map.Entry<String, Long> toAdd = new AbstractMap.SimpleEntry<>(max, revsInBusiness.stream().distinct().count());
                    if(ans.containsKey(i)) ans.get(i).add(toAdd);
                    else{
                        List<Map.Entry<String, Long>> tmpList = new ArrayList<>();
                        tmpList.add(toAdd);
                        ans.put(i, tmpList);
                    }
                    bIDsAndNumberOfOccurrences.remove(max);
                }
                else break;
            }
        }
        return ans;
    }

    /**
     * Method to get a Map associating businesses IDs with their number of reviews
     * @return Map associating businesses IDs with their number of reviews
     */
    public Map<String, Integer> businessesReviewedWithNumberReviews(){
        Map<String, Integer> ans = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            String bID = r.getBusiness_ID();
            if(ans.containsKey(bID))
                ans.put(bID, ans.get(bID) + 1);
            else ans.put(bID, 1);
        }
        return ans;
    }

    /**
     * Auxiliary method to get query 7
     * @param businessesByCity Map associating cities with businesses IDs of each city
     * @return Query 7 answer
     */
    public Map<String, List<String>> query7(Map<String, Set<String>> businessesByCity){
        Map<String, List<String>> ans = new HashMap<>();
        Map<String, Integer> busisReviewed = businessesReviewedWithNumberReviews();
        for(String city : businessesByCity.keySet()){
            Set<String> tmp = businessesByCity.get(city);
            if(tmp != null) {
                tmp.removeIf(s -> !busisReviewed.containsKey(s));
                if (!tmp.isEmpty()) {
                    int max = -1;
                    int secondMax = -1;
                    int thirdMax = -1;
                    String maxS = null;
                    String secondS = null;
                    String thirdS = null;
                    for (String s : tmp) {
                        int analyzing = busisReviewed.get(s);
                        if (analyzing > max) {
                            thirdMax = secondMax;
                            thirdS = secondS;
                            secondMax = max;
                            secondS = maxS;
                            max = analyzing;
                            maxS = s;
                        } else if (analyzing > secondMax) {
                            thirdMax = secondMax;
                            thirdS = secondS;
                            secondMax = analyzing;
                            secondS = s;
                        } else if (analyzing > thirdMax) {
                            thirdMax = analyzing;
                            thirdS = s;
                        }
                    }
                    if (thirdS != null && secondS != null && maxS != null) {
                        if (ans.containsKey(city)) {
                            ans.get(city).add(maxS);
                            ans.get(city).add(secondS);
                            ans.get(city).add(thirdS);
                        } else {
                            List<String> toAdd = new ArrayList<>();
                            toAdd.add(maxS);
                            toAdd.add(secondS);
                            toAdd.add(thirdS);
                            ans.put(city, toAdd);
                        }
                    } else if (secondS != null && maxS != null) {
                        if (ans.containsKey(city)) {
                            ans.get(city).add(maxS);
                            ans.get(city).add(secondS);
                        } else {
                            List<String> toAdd = new ArrayList<>();
                            toAdd.add(maxS);
                            toAdd.add(secondS);
                            ans.put(city, toAdd);
                        }
                    } else if (maxS != null) {
                        if (ans.containsKey(city))
                            ans.get(city).add(maxS);
                        else {
                            List<String> toAdd = new ArrayList<>();
                            toAdd.add(maxS);
                            ans.put(city, toAdd);
                        }
                    }
                }
            }
        }
        return ans;
    }

    /**
     * Method to get List of Reviews
     * @return List of Reviews on the catalog
     */
    public List<ReviewInterface> getListOfRevs(){
        List<ReviewInterface> ans = new ArrayList<>();
        for(ReviewInterface r : this.reviewsSet)
            ans.add(r.clone());
        return ans;
    }

    /**
     * Auxiliary method to get query 8
     * @param limit Number of asked parameters
     * @return Query 8 answer
     */
    public List<Map.Entry<String, Long>> query8(int limit){
        List<ReviewInterface> revs = getListOfRevs();
        return revs.stream()
                .collect(Collectors.groupingBy(ReviewInterface::getUser_ID))
                .entrySet().stream()
                .map(e -> new AbstractMap.SimpleEntry<>(e.getKey(), e.getValue().stream().map(ReviewInterface::getBusiness_ID)
                        .distinct().count())).sorted((e1, e2) -> (e2.getValue().compareTo(e1.getValue())))
                .limit(limit).collect(Collectors.toList());
    }

    /**
     * Method to get a Map associating user ID with pair of number of reviews and total stars
     * @param reviews List of reviews
     * @return Map associating user ID with pair of number of reviews and total stars
     */
    Map<String, Map.Entry<Integer, Float>> getUsersInfoInBusiRevs(List<ReviewInterface> reviews){
        Map<String, Map.Entry<Integer, Float>> ans = new HashMap<>();
        for(ReviewInterface r : reviews){
            if(ans.containsKey(r.getUser_ID())) {
                Map.Entry<Integer, Float> toAdd = new AbstractMap.SimpleEntry<>(ans.get(r.getUser_ID()).getKey() + 1, ans.get(r.getUser_ID()).getValue() + r.getStars());
                ans.put(r.getUser_ID(), toAdd);
            }
            else{
                Map.Entry<Integer, Float> tA = new AbstractMap.SimpleEntry<>(1, r.getStars());
                ans.put(r.getUser_ID(), tA);
            }
        }
        return ans;
    }

    /**
     * Auxiliary method to get query 9
     * @param businessID Business ID
     * @param limit Number of asked parameters
     * @return Query 9 answer
     */
    public List<Map.Entry<String, Float>> query9(String businessID, int limit){
        List<ReviewInterface> revsInBusiness = getRevsInBusiness(businessID);
        Map<String, Map.Entry<Integer, Float>> usersWithTotalStarsAndTotalRevs = getUsersInfoInBusiRevs(revsInBusiness);
        List<Map.Entry<String, Float>> ans = new ArrayList<>();
        for(int i = 0; i < limit; i++){
            int max = 0;
            String maxS = null;
            for(String s : usersWithTotalStarsAndTotalRevs.keySet())
                if(usersWithTotalStarsAndTotalRevs.get(s).getKey() > max){
                    max = usersWithTotalStarsAndTotalRevs.get(s).getKey();
                    maxS = s;
                }
            if(maxS != null){
                Map.Entry<String, Float> toAdd = new AbstractMap.SimpleEntry<>(maxS, usersWithTotalStarsAndTotalRevs.get(maxS).getValue() / usersWithTotalStarsAndTotalRevs.get(maxS).getKey());
                ans.add(toAdd);
                usersWithTotalStarsAndTotalRevs.remove(maxS);
            }
            else break;
        }
        return ans;
    }

    /**
     * Method to get a Map associating businesses IDs with their average grade
     * @return Map associating businesses IDs with their average grade
     */
    public Map<String, Float> businessesReviewedWithAverage(){
        Map<String, Map.Entry<Float, Integer>> mapWithNumberRevsAndTotalClass = new HashMap<>();
        Map<String, Float> ans = new HashMap<>();
        for(ReviewInterface r : this.reviewsSet){
            String bID = r.getBusiness_ID();
            if(mapWithNumberRevsAndTotalClass.containsKey(bID)){
                Map.Entry<Float, Integer> tmp = mapWithNumberRevsAndTotalClass.get(bID);
                Map.Entry<Float, Integer> toAdd = new AbstractMap.SimpleEntry<>(tmp.getKey() + r.getStars(), tmp.getValue() + 1);
                mapWithNumberRevsAndTotalClass.put(bID, toAdd);
            }
            else{
                Map.Entry<Float, Integer> toAdd = new AbstractMap.SimpleEntry<>(r.getStars(), 1);
                mapWithNumberRevsAndTotalClass.put(bID, toAdd);
            }
        }
        for(String s : mapWithNumberRevsAndTotalClass.keySet())
            ans.put(s, mapWithNumberRevsAndTotalClass.get(s).getKey() / mapWithNumberRevsAndTotalClass.get(s).getValue());
        return ans;
    }

    /**
     * Auxiliary method to get query 10
     * @param m Map associating Businesses States with a Map associating Sets of Businesses IDs with their cities
     * @return Query 10 answer
     */
    public Map<String, Map<String, Map<String, Float>>> query10(Map<String, Map<String, Set<String>>> m){
        Map<String, Map<String, Map<String, Float>>> ans = new HashMap<>();
        Map<String, Float> busisReviewed = businessesReviewedWithAverage();
        System.out.println(m);
        for(String state : m.keySet()) {
            Map<String, Set<String>> busis_cities = m.get(state);
            if (ans.containsKey(state)){
                for(String city : busis_cities.keySet()){
                    if(ans.get(state).containsKey(city)){
                        Set<String> busis_busis = busis_cities.get(city);
                        busis_busis.removeIf(b->!busisReviewed.containsKey(b));
                        Map<String, Float> busis_inside = ans.get(state).get(city);
                        for(String b : busis_busis)
                            busis_inside.put(b, busisReviewed.get(b));
                        ans.get(state).put(city, busis_inside);
                    }
                    else{
                        Set<String> busisIDS = busis_cities.get(city);
                        busisIDS.removeIf(b->!busisReviewed.containsKey(b));
                        Map<String, Float> busis_insideTA = new HashMap<>();
                        for(String b : busisIDS)
                            busis_insideTA.put(b, busisReviewed.get(b));
                        ans.get(state).put(city, busis_insideTA);
                    }
                }
            }
            else{
                Map<String, Map<String, Float>> toAdd = new HashMap<>();
                for(String city : busis_cities.keySet()){
                    Set<String> busisIDS = busis_cities.get(city);
                    busisIDS.removeIf(b->!busisReviewed.containsKey(b));
                    Map<String, Float> busis_insideTA = new HashMap<>();
                    for(String b : busisIDS) {
                        busis_insideTA.put(b, busisReviewed.get(b));
                    }
                    toAdd.put(city, busis_insideTA);
                }
                ans.put(state, toAdd);
            }
        }
        return ans;
    }
}
