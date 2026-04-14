phasetable=
{
    {
        type="MidPhase",
        time=360,
        enemytable=
        {
            {
                x=460,
                y=100,
                HP=200,
                start=60,
                End=216000,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    },
                    {
                        type="ScoreDrop1",
                        dropconfig=
                        {
                            droptype="Power",
                            dropnum=80
                        }
                    },
                }
            }
        }
    },

    {
        type="BossPhase",
        spelltable=
        {
            {
                time=120,
                HP=2000,
                spellname=" ",
                name_x=-100,
                name_y=-100,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    }
                }
            },

            {
                time=1800,
                HP=2500,
                spellname="「终忆」吹拂樱花",
                name_x=50,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    },

                    {
                        type="BreezyBlossom1"
                    }
                }
            },

            {
                time=1800,
                HP=2500,
                spellname="「终忆」吹拂樱花",
                name_x=50,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    }
                }
            },

            {
                time=1800,
                HP=2500,
                spellname="「终忆」吹拂樱花",
                name_x=50,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    }
                }
            },

            {
                time=1800,
                HP=2000,
                spellname="「终忆」吹拂樱花",
                name_x=50,
                name_y=25,
                voidspell=false,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    },

                    {
                        type="BreezyBlossom1"
                    },

                    {
                        type="BreezyBlossom2"
                    },

                    {
                        type="BreezyBlossom3"
                    },

                    {
                        type="BreezyBlossom4"
                    }
                }
            }
        }
    }
}