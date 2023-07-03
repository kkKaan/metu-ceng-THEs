package ceng.ceng351.foodrecdb;

public class Includes {
    
    private int itemID;
    private int ingredientID;


    public Includes(int itemID, int ingredientID) {
        this.itemID = itemID;
        this.ingredientID = ingredientID;
    }

    public int getItemID() {
        return itemID;
    }

    public void setItemID(int itemID) {
        this.itemID = itemID;
    }

    public int getIngredientID() {
        return ingredientID;
    }

    public void setIngredientID(int ingredientID) {
        this.ingredientID = ingredientID;
    }

    @Override
    public String toString() {
        return itemID + "\t" + ingredientID;
    }
}
