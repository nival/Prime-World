using System.ComponentModel;
using System.Text.RegularExpressions;
using DBTypes;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Editors.AnimGraph
{
  public class SubNode : NormalNode, IOwnedListElement<RandomNode>
  {
    public SubNode() 
    {
      //этот конструктор нужен только для того, чтобы иметь возможность добавить сабноду из PE
    }

    public SubNode(AnimGraphContext _context, AnGrMacronode _agNode)
      : base (_context, _agNode)
    {
    }

    private RandomNode owner;

    [Browsable(false), HideInOutliner]
    public RandomNode Owner
    {
      get { return owner; }
      set
      {
        owner = value;
        Context = owner.Context;
      }
    }

    [Browsable(false), HideInOutliner]
    public override OutlinerReadOnlyList<Link> Links
    {
      get { return base.Links; }
    }

    [Browsable(false)]
    public override string NextNode 
    {
      get { return base.NextNode; }
      set { base.NextNode = value; } 
    }

    [Browsable(false)]
    public override bool Looped
    {
      get { return NextNode == Owner.Name; }
      set
      {
        Owner.Looped = value;
      }
    }

    [Browsable( false )]
    public override float SurfaceSpeed
    {
      get
      {
        return base.SurfaceSpeed;
      }
      set
      {
        base.SurfaceSpeed = value;
      }
    }

    public float Probability
    {
      get { return Owner.GetSublink(Name).probability; }
      set
      {
        if(value <= 0)
        {
          Log.TraceError("Invalid probability value:{0}", value);
          return;
        }

        var link = Owner.GetSublink(Name);

        link.probability = value;
        
        if (Context != null)
          Context.Controller.SetFlMultiTransactionsInfo(Owner.AnGrNodeIndex, this.AnGrNodeIndex, link);
      }
    }

    [ReadOnly(true)]
    public string ProbabilityPercentage
    {
      set
      {
        int percent = 0;

        var match = Regex.Match(value, @"^\s*(1?\d{1,2})\s*(%|$|\s)");

        bool valid = match.Success && int.TryParse(match.Groups[1].Value, out percent);

        if(!valid)
        {
          Log.TraceError("Invalid value for ProbabilityPercentage: {0}", value);
          return;
        }

        if (percent < 0 || percent > 100 || (percent == 100 && Owner.SubNodes.Count > 1))
        {
          Log.TraceError("Invalid percentage: {0}", percent);
          return;
        }

        float sum = 0;
        foreach (var subNode in Owner.SubNodes)
        {
          if(subNode != this)
            sum += subNode.Probability;
        }

        int sumPercent = 100 - percent;

        Probability = ((sum * 100) / sumPercent) - sum;
      }
      get
      {
        float sum = 0;
        foreach (var subNode in Owner.SubNodes)
        {
          sum += subNode.Probability;
        }

        return string.Format("{0:##0}%", Probability / sum * 100);
      }
    }

    protected override AnGrFlMultiTransaction InitAgLink(Node _toNode)
    {
      var result = new AnGrFlMultiTransaction
      {
        targetNode = _toNode.Name,
        parameters = InitAgLinkParams(_toNode),
        probability = 0
      };

      return result;
    }

    private AnGrFlTransaction InitAgLinkParams(Node _toNode)
    {
      var result = new AnGrFlTransaction();

      if (Owner == _toNode)
      {
        result.fromMin.value = 0.999f;
        result.fromMax.value = 1;
        result.duration = 1.0f / 999.0f;
      }
      else
      {
        result.fromMin.value = 0;
        result.fromMax.value = 1;
        result.duration = 1.0f / 10.0f;
      }

      return result;
    }

    [AnimationSelected]
    public override string Animation
    {
      get
      {
        return base.Animation;
      }
      set
      {
        base.Animation = value;
        Owner.UpdateAnimation();
      }
    }

    public bool IsValid
    {
      get { return Context != null && agNode != null;}
    }

  }
}
