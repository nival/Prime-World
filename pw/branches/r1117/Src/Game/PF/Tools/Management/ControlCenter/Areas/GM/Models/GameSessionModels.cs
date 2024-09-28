

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;

namespace ControlCenter.Areas.GM.Models
{
    public class GameSessionShortInfoModel
    {
        public long GameSessionId { get; set; }
        public IEnumerable<AccountShortInfoModel> TeamDocts { get; set; }
        public IEnumerable<AccountShortInfoModel> TeamAdorni { get; set; }
        public string ErrorIfExistToShow { get; set; }

        public GameSessionShortInfoModel()
        {
        }

        public GameSessionShortInfoModel(GameSessionShortInfo info)
            : this()
        {
            if (info == null)
                throw new ArgumentNullException("info");

            this.GameSessionId = info.Sessionid;
            this.TeamDocts = info.Teamdocts.Select(i => new AccountShortInfoModel(i));
            this.TeamAdorni = info.Teamadorni.Select(i => new AccountShortInfoModel(i));
        }
    }

    public class GameReplayModel
    {
        [DisplayName("Hostname (not neccesary)")]
        public string Hostname { get; set; }

        [Required]
        [DisplayName("Date in YYYY-MM-DD format")]
        public string Date { get; set; }
        [Required]
        [DisplayName("GameSessionId")]
        public string GameSessionId { get; set; }

        public string ErrorIfExistToShow { get; set; }

        public List<GameReplayInfoModel> Replays { get; set; }

        public GameReplayModel()
        {
            Replays = new List<GameReplayInfoModel>();
        }
    }

    public class GameReplayInfoModel
    {
        public string Name { get; set; }
        public string Link { get; set; }
    }
}