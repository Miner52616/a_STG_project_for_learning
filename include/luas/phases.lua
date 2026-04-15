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
                bossname="Matara Okina",
                spellname=" ",
                spellnum=0,
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
                bossname="Matara Okina",
                spellname="「终忆」吹拂樱花",
                spellnum=3,
                name_x=750,
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
                bossname="Matara Okina",
                spellname="「终忆」吹拂樱花",
                spellnum=2,
                name_x=750,
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
                bossname="Matara Okina",
                spellname="「终忆」吹拂樱花",
                spellnum=1,
                name_x=750,
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
                bossname="Matara Okina",
                spellname="「终忆」吹拂樱花",
                spellnum=0,
                name_x=750,
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