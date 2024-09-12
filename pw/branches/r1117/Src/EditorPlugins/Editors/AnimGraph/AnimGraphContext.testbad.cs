using System.Collections.Generic;
using DBTypes;
using NUnit.Framework;
using NUnit.Mocks;

namespace EditorPlugins.Editors.AnimGraph
{
  [TestFixture]
  public class AnimGraphContextTest
  {
    [Test, Description("Test copy node")]
    public void TestCopyNode()
    {
      var agController = new DynamicMock(typeof(IAgController));
      AnimGraphContext context = AnimGraphContext.CreateContext((IAgController)agController.MockInstance);

      Node sourceNode = context.CreateNewNode("node1", EAnGrNodeType.Normal, 0, 0);
      Node newNode = context.CopyNode(sourceNode);

      Assert.IsTrue(newNode.Links.Count == sourceNode.Links.Count, "Links is broken");

      bool isBrokenOutLinks = false;
      for (int i = 0; i < newNode.Links.Count; ++i)
      {
        if (sourceNode.Links[i].ToNode != newNode.Links[i].ToNode)
          isBrokenOutLinks = true;
      }
      Assert.IsFalse(isBrokenOutLinks, "Links is broken");

      List<Node> linkedToSource = new List<Node>();
      List<Node> linkedToNew = new List<Node>();

      foreach (var node in context.ListNodes())
      {
        if (node != sourceNode && node != newNode)
        {
          foreach (var link in node.Links)
          {
            Node n = link.ToNode;

            if (n == sourceNode) linkedToSource.Add(n);
            if (n == newNode) linkedToNew.Add(n);
          }
        }
      }

      Assert.IsTrue(linkedToSource.Count == linkedToNew.Count, "Inner Links is broken");

      bool isBrokenInnerLinks = false;

      for (int i = 0; i < linkedToSource.Count; ++i)
      {
        if (linkedToSource[i] != linkedToNew[i])
          isBrokenInnerLinks = true;
      }

      Assert.IsFalse(isBrokenInnerLinks, "Inner Links is broken");
    }
  }
}
