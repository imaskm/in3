using System;
using System.Collections.Generic;

namespace In3.Storage
{
    public class InMemoryStorage : Storage
    {
        private Dictionary<string, byte[]> cache;

        public InMemoryStorage()
        {
            cache = new Dictionary<string, byte[]>();
        } 

        public byte[] GetItem(string key)
        {
            if (cache.ContainsKey(key)) return cache[key];
            return null;
        }

        public void SetItem(string key, byte[] content)
        {
            if (!String.IsNullOrEmpty(key))
            {
                cache[key] = content;
            }
        }

        public bool Clear()
        {
            cache.Clear();
            return true;
        }
    }
}