import java.awt.Color;
public class PlaylistNode {
	
	static protected Integer order;
	private PlaylistNode parent;
	protected PlaylistNodeType type; // Type needs to be set for proper GUI. Check CengNodeType.java.

	// GUI Accessors - do not modify
	public Integer level;
	public Color color;
	
	public PlaylistNode(PlaylistNode parent) {
		this.parent = parent;
				
		if (parent != null)
		this.level = parent.level + 1;
		else
			this.level = 0;
	}
	
	// Getters-Setters - Do not modify
	public PlaylistNode getParent()
	{
		return parent;
	}
	
	public void setParent(PlaylistNode parent)
	{
		this.parent = parent;
	}
	
	public PlaylistNodeType getType()
	{
		return type;
	}
	
	// GUI Methods - Do not modify
	public Color getColor()
	{
		return this.color;
	}

}
