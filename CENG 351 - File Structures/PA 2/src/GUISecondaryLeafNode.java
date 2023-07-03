import java.awt.Color;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUISecondaryLeafNode extends GUITreeNode {
	public GUISecondaryLeafNode(PlaylistNode node) {
		super(node);

		this.setBackground(Color.pink);

		PlaylistNodeSecondaryLeaf castNode = (PlaylistNodeSecondaryLeaf)node;
		
		for(int i = 0; i < castNode.genreCount(); i++) {
			if(i >= this.labels.size()) {
				System.out.println("Genre count is greater than label count.");
				return;
			}
			
 			String genre = castNode.genreAtIndex(i);
			
			JLabel correspondingLabel = this.labels.get(i);
			
			correspondingLabel.setText(genre);
			correspondingLabel.repaint();
		}
	}
	
	
}
