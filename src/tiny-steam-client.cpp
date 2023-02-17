#include <cstdio>
#include "argparser.hpp"
#include "SteamClient.hpp"
#include "WebApiHelper.hpp"

int main(int argc, char** argv)
{
    InitializeCryptoTool();
	
    ArgParser parser;

    parser.AddOption("-cm", "CM Server socket e.g. 127.0.0.1:27017", OptionAttr::OptionalWithValue, OptionValueType::STRING);
    parser.AddOption("-user", "Steam account username.", OptionAttr::RequiredWithValue, OptionValueType::STRING);
    parser.AddOption("-pw", "Steam account password.", OptionAttr::RequiredWithValue, OptionValueType::STRING);
    parser.AddOption("-tfc", "Steam two factor code.(Received by steam mobile)", OptionAttr::OptionalWithValue, OptionValueType::STRING);
    parser.AddOption("-ac", "Steam auth code.(Received by email)", OptionAttr::OptionalWithValue, OptionValueType::STRING);

    try
    {
        parser.ParseArgument(argc, argv);
    }
    catch (const std::exception& e)
    {
        printf("%s\n", e.what());
        return -1;
    }
    
    SteamClient sclient(parser);

    if (parser.HasOption("-tfc") && parser.HasOption("-ac"))
    {
        printf("Detected both -tfc and -ac provided, you can only provide one of them!\n");
        return -1;
    }

    sclient.SetAccount(parser.GetOptionValueString("-user"), 
        parser.GetOptionValueString("-pw"), 
        parser.GetOptionValueString("-tfc"),
        parser.GetOptionValueString("-ac")
    );

    //We have to get cm server from web api if we don't specify one
    if (parser.HasOption("-cm"))
    {
        sclient.SetCMServer(parser.GetOptionValueString("-cm"));
    }
    else
    {
        if (!SteamWebApiHelper::CheckCachedCMList())
            return -1;

        auto svsocket = SteamWebApiHelper::GetPickedCMServer();
        printf("Randomly picked a CM server: %s\n", svsocket.c_str());
        sclient.SetCMServer(svsocket.c_str());
    }

    sclient.RunClient();
    return 0;
}
