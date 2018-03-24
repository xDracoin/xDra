// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}



class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x6b;
        pchMessageStart[1] = 0xfa;
        pchMessageStart[2] = 0xe4;
        pchMessageStart[3] = 0x7d;
        vAlertPubKey = ParseHex("047557dfe27833869df7a8b8b3f75dab14cbd0e48590569f94a4b23f07ba71f4c46fede7d158689842856b678ec02ce414ef80548643d4bab57ab676d8216276cd");
        nDefaultPort = 18053;
        nRPCPort = 18054;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "WATCH as HUGE band of snow to hit London and South East";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1521921600, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1521921600;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 9980109;
    
        hashGenesisBlock = genesis.GetHash();


//        printf("%s\n", hashGenesisBlock.ToString().c_str());
//        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());

		
        assert(hashGenesisBlock == uint256("6926f7ca57480caaf2dd54aac890d9746dc261479a5c349559e9774e594a80bd"));
        assert(genesis.hashMerkleRoot == uint256("83b9d68327084ee1c3c1c8e06f4fbc5b49a2cfd972b641aac391830168141cfd"));
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,138);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,138);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,138);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        
        vSeeds.push_back(CDNSSeedData("0","199.247.12.72"));
	vSeeds.push_back(CDNSSeedData("1","45.76.212.128"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
     
        strDarksendPoolDummyAddress = "xvhA1ngH4XngPD9U8aXbYzPuQUDiXJZSCV";
        nLastPOWBlock = 2000000; //
        nPOSStartBlock = 3000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf5;
        pchMessageStart[1] = 0x2d;
        pchMessageStart[2] = 0x0a;
        pchMessageStart[3] = 0x06;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04e3a70eb22779e5a6bcd7ddfa7411b6932943d8706d1eadb95f30363362ee43b3045f09fbc049546f16659c6497d27edeabfea6c2b5ed3b7ce3b3aa1bca744f90");
        nDefaultPort = 28053;
        nRPCPort = 28054;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1521230400+120;
        genesis.nNonce = 342;

       if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "testnet.genesis : \n" << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
        }
        //assert(hashGenesisBlock == uint256("6a7cb13f9c1bdd73bc0a76b7a5034e80716fdf6a13d64b7cd5ccba790c8441e7"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,118);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,118);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,128);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,118);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
