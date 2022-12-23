/*
 * lz77.h: common LZ77 compression code between Deflate and LZX.
 */

/*
 * The parameter structure you pass to the lz77.c routines to give
 * them a way to return the compressed output stream.
 */
struct LZ77InternalContext;
struct LZ77Context {
    struct LZ77InternalContext *ictx;
    void *userdata;
    void (*literal) (struct LZ77Context *ctx, unsigned char c);
    void (*match) (struct LZ77Context *ctx, int distance, int len);
};

/*
 * Initialise the private fields of an LZ77Context. It's up to the
 * user to initialise the public fields.
 */
void lz77_init(struct LZ77Context *ctx, int winsize);

/*
 * Clean up the private fields of an LZ77Context.
 */
void lz77_cleanup(struct LZ77Context *ctx);

/*
 * Supply data to be compressed. Will update the private fields of
 * the LZ77Context, and will call literal() and match() to output.
 * If `compress' is false, it will never emit a match, but will
 * instead call literal() for everything.
 */
void lz77_compress(struct LZ77Context *ctx,
                   const unsigned char *data, int len, bool compress);
