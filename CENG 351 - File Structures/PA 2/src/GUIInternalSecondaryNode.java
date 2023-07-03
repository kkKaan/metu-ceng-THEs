import java.awt.Color;

import java.util.ArrayList;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUIInternalSecondaryNode extends GUITreeNode {
	public GUIInternalSecondaryNode(PlaylistNode node) {
		super(node);
		
		this.setBackground(Color.white);

		PlaylistNodeSecondaryIndex castNode = (PlaylistNodeSecondaryIndex)node;
		
		for(int i = 0; i < castNode.genreCount(); i++) {
			if(i < this.labels.size()) {
	 			String genre = castNode.genreAtIndex(i);
				
				JLabel correspondingLabel = this.labels.get(i);
				
				correspondingLabel.setText(genre);
				
				correspondingLabel.repaint();
			}
			else {
				System.out.println("Genre count is greater than label count.");
			}
		}
		
		ArrayList<PlaylistNode> allChildren = castNode.getAllChildren();
		
		if(allChildren.size() > this.paddings.size()) {
			System.out.println("Children count is greater than padding count.");
		}
		
		for(int i = 0; i < this.paddings.size(); i++) {
			if(i < allChildren.size()) {
				PlaylistNode child = allChildren.get(i);
				
				this.paddings.get(i).setBackground(Color.BLUE);				
			}
		}
		
		this.repaint();
	}
}
