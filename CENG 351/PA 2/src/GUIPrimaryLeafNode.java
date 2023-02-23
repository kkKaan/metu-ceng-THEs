import java.awt.Color;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUIPrimaryLeafNode extends GUITreeNode {
	public GUIPrimaryLeafNode(PlaylistNode node) {
		super(node);

		this.setBackground(Color.green);

		PlaylistNodePrimaryLeaf castNode = (PlaylistNodePrimaryLeaf)node;
		
		for(int i = 0; i < castNode.songCount(); i++) {
			if(i >= this.labels.size()) {
				System.out.println("Song count is greater than label count.");
				
				return;
			}
			
 			Integer audioId = castNode.audioIdAtIndex(i);
			 			
			String keyString = "" + audioId;
			
			JLabel correspondingLabel = this.labels.get(i);
			
			correspondingLabel.setText(keyString);
			correspondingLabel.repaint();
		}
	}
}
