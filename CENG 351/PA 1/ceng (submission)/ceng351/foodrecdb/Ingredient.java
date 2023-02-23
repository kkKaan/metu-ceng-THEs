package ceng.ceng351.foodrecdb;

public class Ingredient {

    private int ingredientID;
    private String ingredientName;

    public Ingredient(int ingredientID, String name) {
        this.ingredientID = ingredientID;
        this.ingredientName = name;
    }

    public int getIngredientID() {
        return ingredientID;
    }

    public void setIngredientID(int ingredientID) {
        this.ingredientID = ingredientID;
    }

    public String getIngredientName() {
        return ingredientName;
    }

    public void setIngredientName(String name) {
        this.ingredientName = name;
    }

    @Override
    public String toString() {
        return ingredientID + "\t" + ingredientName;
    }
    
}
