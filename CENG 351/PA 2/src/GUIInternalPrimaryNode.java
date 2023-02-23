import java.awt.Color;

import java.util.ArrayList;

import javax.swing.JLabel;

@SuppressWarnings("serial")
public class GUIInternalPrimaryNode extends GUITreeNode {
	public GUIInternalPrimaryNode(PlaylistNode node) {
		super(node);
		
		this.setBackground(Color.lightGray);

		PlaylistNodePrimaryIndex castNode = (PlaylistNodePrimaryIndex)node;
		
		for(int i = 0; i < castNode.audioIdCount(); i++) {
			if(i < this.labels.size()) {
	 			Integer audioId = castNode.audioIdAtIndex(i);
	 			
				String keyString = "" + audioId;
				
				JLabel correspondingLabel = this.labels.get(i);
				
				correspondingLabel.setText(keyString);
				
				correspondingLabel.repaint();
			}
			else {
				System.out.println("AudioId count is greater than label count.");
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
