import java.awt.FlowLayout;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

@SuppressWarnings("serial")
public class GUILevel extends JPanel {
	private ArrayList<GUITreeNode> allNodes;
	
	public GUILevel() {
		this.allNodes = new ArrayList<GUITreeNode>();
		
		if(CengPlaylist.shouldWrap()) {
			this.setLayout(new WrapLayout(FlowLayout.CENTER, 10, 10));
		}
		else {
			this.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));
		}
		
		this.setOpaque(false);
	}
	
	public void addNode(PlaylistNode node) {
		GUITreeNode newPanel = null;
		
		if(node.getType() == PlaylistNodeType.Internal) {
			newPanel = new GUIInternalPrimaryNode(node);
		}
		else {
			newPanel = new GUIPrimaryLeafNode(node);
		}
		
		this.add(newPanel);
		this.allNodes.add(newPanel);
	}
	
	public void addNode2(PlaylistNode node) {
		GUITreeNode newPanel = null;

		if(node.getType() == PlaylistNodeType.Internal) {
			newPanel = new GUIInternalSecondaryNode(node);
		}
		else {
			newPanel = new GUISecondaryLeafNode(node);
		}
		
		this.add(newPanel);
		this.allNodes.add(newPanel);
	}

	public void paintSearchedNodes(ArrayList<PlaylistNode> visitedNodes) {
		// Normally every level should have only one selected node while searching.
		
		for(PlaylistNode node : visitedNodes) {
			GUITreeNode guiNode = panelForNode(node);
			
			if(guiNode != null) {
				TitledBorder visitedBorder = BorderFactory.createTitledBorder("Visited");
				visitedBorder.setBorder(BorderFactory.createMatteBorder(5, 5, 5, 5, node.getColor()));
				
				guiNode.setBorder(visitedBorder);
			}	
		}
	}
	
	private GUITreeNode panelForNode(PlaylistNode nodeToSearch) {
		for(GUITreeNode guiNode : this.allNodes) {
			if(guiNode.node.equals(nodeToSearch)) {
				return guiNode;
			}
		}
		
		return null;
	}
}
