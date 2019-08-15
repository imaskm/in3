package in3.eth1;

import in3.*;
import java.math.*;

/**
 * represents a Block in ethereum.
 * 
 */

public class Block {

    /**
     * The latest Block Number.
     */
    public static long LATEST = -1;

    /**
     * The Genesis Block.
     */
    public static long EARLIEST = 0;

    private JSON data;

    private Block(JSON data) {
        this.data = data;
    }

    protected static Block asBlock(Object o) {
        if (o == null)
            return null;
        return new Block((JSON) o);
    }

    protected static Block[] asBlocks(Object o) {
        if (o == null)
            return null;
        Object[] a = (Object[]) o;
        Block[] b = new Block[a.length];
        for (int i = 0; i < a.length; i++)
            b[i] = Block.asBlock(a[i]);
        return b;
    }

    /**
     * returns the total Difficulty as a sum of all difficulties starting from
     * genesis.
     */
    public BigInteger getTotalDifficulty() {
        return data.getBigInteger("totalDifficulty");
    }

    /**
     * the gas limit of the block.
     */
    public BigInteger getGasLimit() {
        return data.getBigInteger("gasLimit");
    }

    /**
     * the extra data of the block.
     */
    public String getExtraData() {
        return data.getString("extraData");
    }

    /**
     * the difficulty of the block.
     */
    public BigInteger getDifficulty() {
        return data.getBigInteger("difficulty");
    }

    /**
     * the author or miner of the block.
     */
    public String getAuthor() {
        return data.getString("author");
    }

    /**
     * the roothash of the merkletree containing all transaction of the block.
     */
    public String getTransactionsRoot() {
        return data.getString("transactionsRoot");
    }

    /**
     * the roothash of the merkletree containing all transaction receipts of the
     * block.
     */
    public String getTransactionReceiptsRoot() {
        return data.getString("receiptsRoot");
    }

    /**
     * the roothash of the merkletree containing the complete state.
     */
    public String getStateRoot() {
        return data.getString("stateRoot");
    }

    /**
     * the transaction hashes of the transactions in the block.
     */
    public String[] getTransactionHashes() {
        Object[] tx = (Object[]) data.get("transactions");
        if (tx == null || tx.length == 0)
            return new String[0];
        if (tx[0] instanceof String)
            return data.getStringArray("transactions");
        String[] res = new String[tx.length];
        for (int i = 0; i < tx.length; i++)
            res[i] = ((JSON) tx[i]).getString("hash");
        return res;
    }

    /**
     * the transactions of the block.
     * 
     * @throws if the Transactions are noot available
     */
    public Transaction[] getTransactions() throws Exception {
        Object[] tx = (Object[]) data.get("transactions");
        if (tx == null || tx.length == 0)
            return new Transaction[0];

        if (tx[0] instanceof String)
            throw new Exception("The Block only contains the transaction hashes!");

        Transaction[] res = new Transaction[tx.length];
        for (int i = 0; i < tx.length; i++)
            res[i] = Transaction.asTransaction(tx[i]);
        return res;
    }

    /**
     * the unix timestamp in seconds since 1970.
     */
    public long getTimeStamp() {
        return data.getLong("timestamp");
    }

    /**
     * the roothash of the merkletree containing all uncles of the block.
     */
    public String getSha3Uncles() {
        return data.getString("sha3Uncles");
    }

    /**
     * the size of the block.
     */
    public long getSize() {
        return data.getLong("size");
    }

    /**
     * the seal fields used for proof of authority.
     */
    public String[] getSealFields() {
        return data.getStringArray("sealFields");
    }

    /**
     * the block hash of the of the header.
     */
    public String getHash() {
        return data.getString("hash");
    }

    /**
     * the bloom filter of the block.
     */
    public String getLogsBloom() {
        return data.getString("logsBloom");
    }

    /**
     * the mix hash of the block. (only valid of proof of work)
     */
    public String getMixHash() {
        return data.getString("mixHash");
    }

    /**
     * the mix hash of the block. (only valid of proof of work)
     */
    public String getNonce() {
        return data.getString("nonce");
    }

    /**
     * the block number
     */
    public long getNumber() {
        return data.getLong("number");
    }

    /**
     * the hash of the parent-block.
     */
    public String getParentHash() {
        return data.getString("parentHash");
    }

    /**
     * returns the blockhashes of all uncles-blocks.
     */
    public String[] getUncles() {
        return data.getStringArray("uncles");
    }

}