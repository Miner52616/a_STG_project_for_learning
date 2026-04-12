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
                HP=600,
                voidspell=true,
                behaviortable=
                {
                    {
                        type="MoveToRandom1"
                    }
                }
            },

            {
                time=1200,
                HP=1000,
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
                time=1200,
                HP=1000,
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
                time=1200,
                HP=1000,
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
                time=1200,
                HP=1000,
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