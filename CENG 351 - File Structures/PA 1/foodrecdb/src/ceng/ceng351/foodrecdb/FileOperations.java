package ceng.ceng351.foodrecdb;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


public class FileOperations {

    public static FileWriter createFileWriter( String path) throws IOException {
        File f = new File( path);

        FileWriter fileWriter = null;

        if( f.isDirectory() && !f.exists())
            f.mkdirs();
        else if( !f.isDirectory() && !f.getParentFile().exists())
            f.getParentFile().mkdirs();

        if( !f.isDirectory() && f.exists())
            f.delete();

        fileWriter = new FileWriter( f, false);

        return fileWriter;
    }

    public static MenuItem[] readItemFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 

        String strLine;

        List<MenuItem> itemList = new ArrayList<>();
        MenuItem[] itemArray = null;
        
        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //itemID    name    cuisine price

            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 4) {
                    System.out.println("There is a problem in MenuItem File Reading phase");
                } 
                else {
                    int itemID = Integer.parseInt(words[0]);
                    String name = words[1];
                    String cuisine = words[2];
                    int price = Integer.parseInt(words[3]);

                    MenuItem item = new MenuItem(itemID, name, cuisine, price);
                    itemList.add(item);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            itemArray = new MenuItem[itemList.size()];
            itemList.toArray(itemArray);

        } 
        catch (IOException e) {
            e.printStackTrace();
        }
        
        return itemArray;
    }

    public static Ingredient[] readIngredientFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null;
        String strLine;

        List<Ingredient> ingredientList = new ArrayList<>();
        Ingredient[] ingredientArray = null;

        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //ingredientID	name
            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");

                if (words.length < 2) {
                    System.out.println("There is a problem in Ingredient File Reading phase");
                }
                else {
                    int ingredientID = Integer.parseInt(words[0]);
                    String name = words[1];

                    Ingredient ingredient = new Ingredient(ingredientID, name);
                    ingredientList.add(ingredient);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            ingredientArray = new Ingredient[ingredientList.size()];
            ingredientList.toArray(ingredientArray);

        }
        catch (IOException e) {
            e.printStackTrace();
        }

        return ingredientArray;
    }

    public static Includes[] readIncludesFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null;
        String strLine;

        List<Includes> includesList = new ArrayList<>();
        Includes[] includesArray = null;

        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //itemID    ingredientID
            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");

                if (words.length < 2) {
                    System.out.println("There is a problem in Includes File Reading phase");
                }
                else {
                    int itemID = Integer.parseInt(words[0]);
                    int ingredientID = Integer.parseInt(words[1]);

                    Includes includes = new Includes(itemID, ingredientID);
                    includesList.add(includes);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            includesArray = new Includes[includesList.size()];
            includesList.toArray(includesArray);

        }
        catch (IOException e) {
            e.printStackTrace();
        }

        return includesArray;
    }

    public static Rating[] readRatingFile(String pathToFile){

        FileReader fileReader = null;
        BufferedReader bufferedReader = null;

        String strLine;

        List<Rating> ratingList = new ArrayList<>();
        Rating[] ratingArray = null;

        try {

            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //ratingID	itemID	rating	ratingDate

            while((strLine = bufferedReader.readLine())!=null) {

                //parse strLine
                String[] words = strLine.split("\t");

                if (words.length < 4) {
                    System.out.println("There is a problem in Ratings File Reading phase");
                }
                else {
                    int ratingID = Integer.parseInt(words[0]);
                    int itemID = Integer.parseInt(words[1]);
                    int rating = Integer.parseInt(words[2]);
                    String ratingDate = words[3];

                    Rating newRating = new Rating(ratingID, itemID, rating, ratingDate);
                    ratingList.add(newRating);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            ratingArray = new Rating[ratingList.size()];
            ratingList.toArray(ratingArray);

        }
        catch (IOException e) {
            e.printStackTrace();
        }

        return ratingArray;
    }

    public static DietaryCategory[] readDietaryCategoryFile(String pathToFile) {
        
        FileReader fileReader = null;
        BufferedReader bufferedReader = null; 
        String strLine;
        List<DietaryCategory> categoryList = new ArrayList<>();
        DietaryCategory[] categoryArray = null;
        
        try {
            fileReader = new FileReader(pathToFile);
            bufferedReader = new BufferedReader(fileReader);

            //example strline
            //ingredientID	name    type

            while((strLine = bufferedReader.readLine())!=null){

                //parse strLine
                String[] words = strLine.split("\t");
                
                if (words.length < 2) {
                    System.out.println("There is a problem in Dietary Category File Reading phase");
                } 
                else {
                    int ingredientID = Integer.parseInt(words[0]);
                    String dietaryCategory = words[1];

                    DietaryCategory category = new DietaryCategory(ingredientID, dietaryCategory);
                    categoryList.add(category);
                }

            }//End of while

            //Close bufferedReader
            bufferedReader.close();

            categoryArray = new DietaryCategory[categoryList.size()];
            categoryList.toArray(categoryArray);

        } 
        catch (IOException e) {
            e.printStackTrace();
        }

        return categoryArray;

    }
    

    

    


}
